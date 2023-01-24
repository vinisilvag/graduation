# Aluno: Vinicius Silva Gomes - 2021421869
# Disciplina: Organização de Computadores I
# Professor: Daniel Fernandes Macedo

main:
    jal x1, calculate_seq # Chama o método que calcula a sequência

calculate_seq:
    addi x5, x0, 1 # Declara i
    
    jal x1, loop   # Chama o loop principal da execução
    
loop:
    beq x5, x10, done     # Caso a condição do loop tenha sido ultrapassada, chama o 'done'
    
    beq x11, x7 force_end # Caso o valor da sequencia seja 1, significa que ela terminou, força o término do loop e retorna 0 em x10
    
    remu x30, x11, x29    # Resto de x11 dividido por 2
    beq x30, x0, even     # Compara se o resto é 0 (número par ou não)
    mul x11, x11, x31     # x11 * 3
    addi x11, x11, 1      # (x11 * 3) + 1
    
    addi x5, x5, 1        # Incrementa o i
    beq x0, x0, loop      # Chama o loop novamente
    
done:
    add x10, x0, x11 # Soma x11 em x10
    jal x0, exit     # Retorna

force_end:
    sub x10, x10, x10 # Subtrai x10 para 0
    jal x0, exit      # Retorna
    
even:
    div x11, x11, x29 # Divide x11 por 2
    
    addi x5, x5, 1    # Incrementa o i
    beq x0, x0, loop  # Chama o loop novamente

exit: # Finaliza o código
