from csv import reader
import pandas as pd

CSV_PATH = "BH.csv"

def format_input_values(value):
  if value != "":
    return "'" + value + "'"
  else:
    return "NULL"

def format_race(race):
  return {
    "": "NULL",
    "1": "'Branca'",
    "2": "'Preta'",
    "3": "'Amarela'",
    "4": "'Parda'",
    "5": "'Indígena'",
    "9": "'Ignorado'",
  }[race]

def format_schooling(schooling):
  return {
    "": "NULL",
    "0": "'Sem escolaridade/Analfabeto'",
    "1": "'Fundamental 1º ciclo (1ª a 5ª série)'",
    "2": "'Fundamental 2º ciclo (6ª a 9ª série)'",
    "3": "'Médio (1º ao 3º ano)'",
    "4": "'Superior'",
    "5": "'Não se aplica'",
    "9": "'Ignorado'",
  }[schooling]

def format_pregnant(pregnant):
  if pregnant == "" or int(pregnant) == 9:
    return "0"

  if int(pregnant) > 3:
    return '0'
  else:
    return '1'

def format_zone(zone):
  return {
    "": "NULL",
    "1": "'Urbana'",
    "2": "'Rural'",
    "3": "'Periurbana'",
    "9": "'Ignorado'",
  }[zone]

def format_hospitalization(hospitalization):
  if hospitalization == "" or int(hospitalization) == 9:
    return "0"

  if int(hospitalization) == 1:
    return '1'
  else:
    return '0'

def format_discharge_or_death(discharge_or_death):
  return {
    "": "NULL",
    "1": "'Cura'",
    "2": "'Óbito'",
    "3": "'Óbito por outras causas'",
    "9": "'Ignorado'",
  }[discharge_or_death]

def format_covid_vaccine(covid_vaccine):
  if covid_vaccine == "" or int(covid_vaccine) == 9:
    return "0"

  if int(covid_vaccine) == 1:
    return '1'
  else:
    return '0'

def format_final_classification(final_classification):
  return {
    "": "NULL",
    "1": "'SRAG por influenza'",
    "2": "'SRAG por outro vírus respiratório'",
    "3": "'SRAG por outro agente etiológico'",
    "4": "'SRAG não especificado'",
    "5": "'SRAG por covid-19'",
  }[final_classification]

class Patient:
  def __init__(self, race, schooling, gender, birth_date, pregnant, state, city, zone, hospitalization, discharge_or_death, first_symptoms_date, discharge_or_death_date, register_date, covid_vaccine, final_classification, cnes):
    self.race = format_race(race)
    self.schooling = format_schooling(schooling)
    self.gender = format_input_values(gender)
    self.birth_date = format_input_values(birth_date)
    self.pregnant = format_pregnant(pregnant)
    self.state = format_input_values(state)
    self.city = format_input_values(city)
    self.zone = format_zone(zone)
    self.hospitalization = format_hospitalization(hospitalization)
    self.discharge_or_death = format_discharge_or_death(discharge_or_death)
    self.first_symptoms_date = format_input_values(first_symptoms_date)
    self.discharge_or_death_date = format_input_values(discharge_or_death_date)
    self.register_date = format_input_values(register_date)
    self.covid_vaccine = format_covid_vaccine(covid_vaccine)
    self.final_classification = format_final_classification(final_classification)
    self.cnes = format_input_values(cnes)

  def sql_insert(self):
    sql_query = "INSERT INTO Paciente (Raca, Escolaridade, Sexo, DataNascimento, Gestante, UF, Municipio, Zona, Internacao, AltaOuObito, DataPrimeirosSintomas, DataAltaOuObito, DataRegistro, VacinaCOVID, ClassificacaoFinal, CNES) VALUES (" + self.race + ", " + self.schooling + ", " + self.gender + ", " + self.birth_date + ", " + self.pregnant + ", " + self.state + ", " + self.city + ", " + self.zone + ", " + self.hospitalization + ", " + self.discharge_or_death + ", " + self.first_symptoms_date + ", " + self.discharge_or_death_date + ", " + self.register_date + ", " + self.covid_vaccine + ", " + self.final_classification + ", " + self.cnes + ");\n"

    return sql_query

class Symptom:
  def __init__(self, name, description):
    self.name = name
    self.description = description

  def sql_insert(self):
    sql_query = "INSERT INTO Sintomas (NomeSintoma, Descricao) VALUES ('" + self.name + "', '" + self.description + "');\n"

    return sql_query

class RiskFactor:
  def __init__(self, name, description):
    self.name = name
    self.description = description

  def sql_insert(self):
    sql_query = "INSERT INTO FatoresRisco (NomeFator, Descricao) VALUES ('" + self.name + "', '" + self.description + "');\n"

    return sql_query

class HealthCenter:
  def __init__(self, cnes, name, state, city):
    self.cnes = cnes
    self.name = name
    self.state = state
    self.city = city

  def __eq__(self, other):
    return self.cnes == other.cnes

  def sql_insert(self):
    sql_query = "INSERT INTO UnidadeSaude (CNES, Nome, UF, Municipio) VALUES ('" + self.cnes + "', '" + self.name + "', '" + self.state + "', '" + self.city + "');\n"

    return sql_query

class PatientSymptom:
  def __init__(self, patient_id, symptom_id):
    self.patient_id = patient_id
    self.symptom_id = symptom_id

  def sql_insert(self):
    sql_query = "INSERT INTO PacienteSintomas (IDPaciente, IDSintoma) VALUES ('" + self.patient_id + "', '" + self.symptom_id + "');\n"

    return sql_query

class PatientRiskFactor:
  def __init__(self, patient_id, risk_factor_id):
    self.patient_id = patient_id
    self.risk_factor_id = risk_factor_id

  def sql_insert(self):
    sql_query = "INSERT INTO PacienteFatores (IDPaciente, IDFator) VALUES ('" + self.patient_id + "', '" + self.risk_factor_id + "');\n"

    return sql_query

def symptom_schema():
  schema = """CREATE TABLE Sintomas(
    IDSintoma INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    NomeSintoma VARCHAR(32),
    Descricao VARCHAR(1024)
);\n
"""

  return schema

def process_symptoms():
  symptoms = [
    Symptom(
      "Febre",
      "Elevação da temperatura corporal acima de um valor normal, estabelecido entre 36,7ºC e 37ºC, quando medida na boca."
    ),
    Symptom(
      "Tosse",
      "Expulsão súbita e ruidosa de ar pela boca, visando, habitualmente, à eliminação de matéria estranha nas vias aéreas."
    ),
    Symptom(
      "Dor de Garganta",
      "É a dor resultante da inflamação das amígdalas (tonsilite) ou da faringe (faringite). Esta situação pode ocorrer por causas diversas, dentre elas a alérgica, a viral, a bacteriana e a traumática."
    ),
    Symptom("Dispneia", "Sensação subjetiva de falta de ar."),
    Symptom(
      "Desconforto Respiratório",
      "O desconforto respiratório surge como consequência de um desequilíbrio entre os níveis de oxigênio e gás carbônico no sangue. O desconforto respiratório ocorre quando o corpo tem dificuldades para realizar as trocas gasosas normais, necessárias para manter o corpo funcionando. "
    ),
    Symptom(
      "Diarréia", 
      "Aumento do volume, frequência ou quantidade de líquido nas evacuações. Deve ser a manifestação mais frequente de alteração da absorção ou transporte intestinal de substâncias, alterações estas que em geral são devidas a uma infecção bacteriana ou viral, a toxinas alimentares, etc."
    ),
    Symptom(
      "Vômito",
      "Ação de vomitar; emissão violenta, pela boca, de conteúdo gástrico, por contração do diafragma e da musculatura do estômago."
    ),
    Symptom(
      "Dor Abdominal",
      "Dor abdominal é aquela sentida em qualquer região entre o tórax e a virilha. Essa área é popularmente conhecida como barriga."
    ),
    Symptom(
      "Fadiga", 
      "Cansaço; estado que vem após o trabalho excessivo ou atividade exagerada de um órgão ou de um organismo."
    ),
    Symptom(
      "Perda de Olfato",
      "É a perda parcial ou completa do sentido. Costuma estar diretamente ligada com a perda do paladar."
    ),
    Symptom(
      "Perda de Paladar",
      "É a perda parcial ou completa do sentido. Costuma estar diretamente ligada com a perda do olfato."
    ),
  ]

  all_symptoms = ''

  for symptom in symptoms:
    all_symptoms += symptom.sql_insert()

  all_symptoms += '\n'

  return all_symptoms

def risk_factor_schema():
  schema = """CREATE TABLE FatoresRisco(
    IDFator INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    NomeFator VARCHAR(32),
    Descricao VARCHAR(1024)
);\n
"""

  return schema

def process_risk_factors():
  risk_factors = [
    RiskFactor(
      "Doença Cardiovascular Crônica",
      "As doenças cardiovasculares se caracterizam por um conjunto de disfunções que atingem o coração e os vasos sanguíneos."
    ),
    RiskFactor(
      "Doença Hematológica Crônica",
      "As doenças hematológicas são aquelas que comprometem a produção dos componentes do sangue, como as hemácias (glóbulos vermelhos), os leucócitos (glóbulos brancos) e as plaquetas, geradas na medula óssea."
    ),
    RiskFactor(
      "Síndrome de Down",
      "Síndrome de Down é uma alteração genética causada por erro na divisão celular. As pessoas apresentam características como olhos oblíquos, rosto arredondado, mãos menores e comprometimento intelectual."
    ),
    RiskFactor(
      "Doença Hepática Crônica",
      "Doença hepática crônica (DHC) é qualquer forma de doença hepática avançada, em que o fígado foi exposto, de forma continuada, a uma ou várias formas de agressão."
    ),
    RiskFactor(
      "Asma",
      "A asma é uma doença inflamatória crônica dos brônquios que se inicia, habitualmente, na infância, mas que pode surgir em qualquer idade."
    ),
    RiskFactor(
      "Diabetes Mellitus",
      "Diabetes Mellitus é uma doença caracterizada pela elevação da glicose no sangue (hiperglicemia). Pode ocorrer devido a defeitos na secreção ou na ação do hormônio insulina, que é produzido no pâncreas, pelas chamadas células beta."
    ),
    RiskFactor(
      "Doença Neurológica Crônica",
      "Entre as condições neurológicas crônicas estão doenças cerebrovasculares (acidente vascular cerebral isquêmico ou hemorrágico, ataque isquêmico transitório e demência vascular) e doenças neurológicas crônicas que impactem a função respiratória."
    ),
    RiskFactor(
      "Pneumopatia Crônica",
      "As pneumopatias são doenças em que há o comprometimento dos pulmões, o que pode acontecer devido à presença de microrganismos, como bactérias ou parasitas, ou ser consequência da inalação de substâncias durante a atividade profissional, como poeira ou amianto, por exemplo, o que pode levar ao aparecimento de alguns sintomas como tosse, febre e falta de ar."
    ),
    RiskFactor(
      "Imunodeficiência ou Imunodepressão",
      "Imunodeficiência é um grupo de doenças, caracterizadas por um ou mais defeitos do sistema imunológico. Como conseqüência destas alterações, o indivíduo se torna mais propenso a apresentar grande número de infecções."
    ),
    RiskFactor(
      "Doença Renal Crônica",
      "A doença renal crônica é uma diminuição lenta e progressiva (durante meses ou anos) da capacidade dos rins de filtrar os resíduos metabólicos do sangue. As causas principais são diabetes e pressão arterial alta."
    ),
    RiskFactor(
      "Obesidade",
      "A obesidade é o acúmulo de gordura no corpo causado quase sempre por um consumo de energia na alimentação, superior àquela usada pelo organismo para sua manutenção e realização das atividades do dia-a-dia. Ou seja: a ingestão alimentar é maior que o gasto energético correspondente."
    ),
  ]

  all_risk_factors = ''

  for risk_factor in risk_factors:
    all_risk_factors += risk_factor.sql_insert()

  all_risk_factors += '\n'

  return all_risk_factors

def health_center_schema():
  schema = """CREATE TABLE UnidadeSaude(
    CNES VARCHAR(16) PRIMARY KEY NOT NULL,
    Nome VARCHAR(32),
    UF VARCHAR(2),
    Municipio VARCHAR(32)
);\n
"""

  return schema

def process_health_centers():
  health_centers = []

  raw_data = pd.read_csv(CSV_PATH)

  with open(CSV_PATH, 'r') as read_obj:
    raw_data = reader(read_obj)
    headers = next(raw_data)

    if headers != None:
      for item in raw_data:
        health_center = HealthCenter(item[5], item[4], item[2], item[3])

        if health_center not in health_centers:
          health_centers.append(health_center)

  all_health_centers = ''

  for health_center in health_centers:
    all_health_centers += health_center.sql_insert()

  all_health_centers += '\n'

  return all_health_centers

def patient_schema():
  schema = """CREATE TABLE Paciente(
    IDPaciente INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    Raca VARCHAR(32),
    Escolaridade VARCHAR(32),
    Sexo VARCHAR(1),
    DataNascimento TEXT,
    Gestante INTEGER,
    UF VARCHAR(2),
    Municipio VARCHAR(32),
    Zona VARCHAR(16),
    Internacao INTEGER,
    AltaOuObito VARCHAR(32),
    DataPrimeirosSintomas TEXT,
    DataAltaOuObito TEXT,
    DataRegistro TEXT,
    VacinaCOVID INTEGER,
    ClassificacaoFinal VARCHAR(32),
    CNES REFERENCES UnidadeSaude (CNES)
);\n
"""

  return schema

def process_patients():
  patients = []

  raw_data = pd.read_csv(CSV_PATH)

  with open(CSV_PATH, 'r') as read_obj:
    raw_data = reader(read_obj)
    headers = next(raw_data)

    if headers != None:
      for item in raw_data:
        patient = Patient(item[9], item[10], item[6], item[7], item[8], item[29], item[11], item[12], item[20], item[22], item[1], item[23], item[0], item[28], item[21], item[5])
        patients.append(patient)

  all_patients = ''

  for patient in patients:
    all_patients += patient.sql_insert()

  all_patients += '\n'

  return all_patients

def patients_symptoms_schema():
  schema = """CREATE TABLE PacienteSintomas(
    IDPaciente INTEGER NOT NULL REFERENCES Paciente (IDPaciente) ON DELETE CASCADE,
    IDSintoma INTEGER NOT NULL REFERENCES Sintomas (IDSintoma)
);\n
"""

  return schema

def process_patients_symptoms():
  patients_symptoms = []

  raw_data = pd.read_csv(CSV_PATH)

  with open(CSV_PATH, 'r') as read_obj:
    raw_data = reader(read_obj)
    headers = next(raw_data)

    count = 1

    if headers != None:
      for item in raw_data:
        if(item[13] != "" and int(item[13]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(1)))
        
        if(item[14] != "" and int(item[14]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(2)))
        
        if(item[15] != "" and int(item[15]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(3)))

        if(item[16] != "" and int(item[16]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(4)))

        if(item[17] != "" and int(item[17]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(5)))

        if(item[18] != "" and int(item[18]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(6)))

        if(item[19] != "" and int(item[19]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(7)))

        if(item[24] != "" and int(item[24]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(8)))

        if(item[25] != "" and int(item[25]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(9)))

        if(item[26] != "" and int(item[26]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(10)))

        if(item[27] != "" and int(item[27]) == 1):
          patients_symptoms.append(PatientSymptom(str(count), str(11)))

        count += 1


  all_patients_symptoms = ''

  for patient_symptom in patients_symptoms:
    all_patients_symptoms += patient_symptom.sql_insert()

  all_patients_symptoms += '\n'

  return all_patients_symptoms

def patients_risk_factors_schema():
  schema = """CREATE TABLE PacienteFatores(
    IDPaciente INTEGER NOT NULL REFERENCES Paciente (IDPaciente) ON DELETE CASCADE,
    IDFator INTEGER NOT NULL REFERENCES FatoresRisco (IDFator)
);\n
"""

  return schema

def process_patients_risk_factors():
  patients_risk_factors = []

  raw_data = pd.read_csv(CSV_PATH)

  with open(CSV_PATH, 'r') as read_obj:
    raw_data = reader(read_obj)
    headers = next(raw_data)

    count = 1

    if headers != None:
      for item in raw_data:
        if(item[30] != "" and int(item[30]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(1)))
        
        if(item[31] != "" and int(item[31]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(2)))
        
        if(item[32] != "" and int(item[32]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(3)))

        if(item[33] != "" and int(item[33]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(4)))

        if(item[34] != "" and int(item[34]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(5)))

        if(item[35] != "" and int(item[35]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(6)))

        if(item[36] != "" and int(item[36]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(7)))

        if(item[37] != "" and int(item[37]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(8)))

        if(item[38] != "" and int(item[38]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(9)))

        if(item[39] != "" and int(item[39]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(10)))

        if(item[40] != "" and int(item[40]) == 1):
          patients_risk_factors.append(PatientRiskFactor(str(count), str(11)))

        count += 1

  all_patients_risk_factors = ''

  for patient_risk_factor in patients_risk_factors:
    all_patients_risk_factors += patient_risk_factor.sql_insert()

  return all_patients_risk_factors

def main():
    file = open('database.sql', 'w+')

    file.write('BEGIN TRANSACTION;\n')

    symptoms = process_symptoms()
    file.write(symptom_schema())
    file.write(symptoms)

    risk_factors = process_risk_factors()
    file.write(risk_factor_schema())
    file.write(risk_factors)

    health_centers = process_health_centers()
    file.write(health_center_schema())
    file.write(health_centers)

    patients = process_patients()
    file.write(patient_schema())
    file.write(patients)

    patients_symptoms = process_patients_symptoms()
    file.write(patients_symptoms_schema())
    file.write(patients_symptoms)

    patients_risk_factors = process_patients_risk_factors()
    file.write(patients_risk_factors_schema())
    file.write(patients_risk_factors)

    file.write('COMMIT;\n')

    file.write('PRAGMA foreign_keys=on;\n')

    file.close()

if __name__ == "__main__":
    main()