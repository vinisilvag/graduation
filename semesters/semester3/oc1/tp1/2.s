# Aluno: Vinicius Silva Gomes - 2021421869
# Disciplina: Organização de Computadores I
# Professor: Daniel Fernandes Macedo

main:
    add x12, x0, x0 		      # Reseta o valor de x12 (i) para 0
    addi x31, x0, 4 		      # Constante == 4
    jal x1, recursive_selection_sort  # Chama o Selection Sort recursivo
    
recursive_selection_sort:
    add x7, x0, x12   # Valor minimo do corte x7 -> min = i
    addi x28, x12, 1  # Declara o valor de x28 -> j = i + 1
    
    jal x1, loop      # Chama o loop 
    
loop:
    beq x28, x11, done      # Caso a condição do loop tenha sido ultrapassada, chama o 'done'
    
    mul x30, x28, x31  
    add x30, x30, x10       # Calcula a posição de j na memória
    lw x5, 0(x30)           # Acessa o array na posição j
    
    mul x30, x7, x31
    add x30, x30, x10       # Calcula a posição de min na memória
    lw x29, 0(x30)          # Acessa o array na posição min
    
    blt x5, x29, change_min # Salva a posição com o menor valor do vetor
    
    addi x28, x28, 1        # Incrementa o j
    beq x0, x0, loop        # Chama o loop novamente
    
change_min:
    add x7, x0, x28    # Faz x7 -> min = j
    
    addi x28, x28, 1   # Incrementa o j
    beq x0, x0, loop   # Chama o loop novamente
    
done:
    mul x21, x7, x31
    add x21, x21, x10   # Calcula a posição de min na memória
    lw x22, 0(x21)      # Acessa o array na posição min
    
    mul x23, x12, x31
    add x23, x23, x10   # Calcula a posição de i na memória
    lw x24, 0(x23)      # Acessa o array na posição i
    
    sw x24, 0(x21)      # Troca a posição de min com i
    sw x22, 0(x23)      # Troca a posição de i com min
    
    addi x12, x12, 1    # Faz i - i + 1
    bge x12, x11, exit  # Se i superar o tamanho do vetor finaliza a execução
    
    jal x1, recursive_selection_sort # Chama a função de maneira recursiva
    
exit: # Finaliza o código
