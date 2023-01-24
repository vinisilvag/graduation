import numpy as np

nome = "Vinicius Silva Gomes"
matricula = 2021421869

def EP_answers(A, B):
    import numpy as np
    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    np.random.seed(1)
    U, Sigma, Sigma_vet, Vt, imgReconst_3, log_Sigma, cumul_Sigma, rmseReconst_3 = [None]*8
    imgReconst_10, rmseReconst_10, imgReconst_100 = [None]*3
    rmseReconst_100, imgReconst_500, rmseReconst_500 = [None]*3
    uso_k_10, uso_k_100, uso_k_500, lim_energ = [None]*4
    B_media, Bm, S, w2, V2, valores_sing, Sigma_vals_sing, Sigma_inv, U2_10, imgs2_10 = [None]*10
    #########################################################################

    ### PARTE 1

    ## 1.1
    U, Sigma_vet, Vt = np.linalg.svd(A)
    
    ## 1.2
    Sigma = np.diag(Sigma_vet)
    
    ## 1.3
    def reconstrucao_aproximada(U, Sigma, Vt, k):
        U_new = U[:, :k]
        Vt_new = Vt[:k,:]
        S_new = np.zeros((k, k))
    
        for i in range(k):
            S_new[i, i] = Sigma[i][i]
                
        return np.dot(np.dot(U_new, S_new), Vt_new)
    
    imgReconst_3 = reconstrucao_aproximada(U, Sigma, Vt, 3)
    
    ## 1.4
    log_Sigma = np.log(Sigma_vet)
    cumul_Sigma = np.cumsum(Sigma_vet)
    
    ## 1.5
    def calcula_RMSE(source, compressed):
        diff = source - compressed
        return np.linalg.norm(diff) / np.sqrt(diff.size)
    
    rmseReconst_3 = calcula_RMSE(A, imgReconst_3)
    
    ## 1.6
    imgReconst_10 = reconstrucao_aproximada(U, Sigma, Vt, 10)
    rmseReconst_10 = calcula_RMSE(A, imgReconst_10)

    imgReconst_100 = reconstrucao_aproximada(U, Sigma, Vt, 100)
    rmseReconst_100 = calcula_RMSE(A, imgReconst_100)

    imgReconst_500 = reconstrucao_aproximada(U, Sigma, Vt, 500)
    rmseReconst_500 = calcula_RMSE(A, imgReconst_500)
    
    ## 1.7
    def calcula_qtd_elementos(U, Sigma_vet, Vt, k):
        U_new = U[:, :k]
        Vt_new = Vt[:k,:]
        S_new = Sigma_vet[:k]
                        
        return (U_new.size + S_new.size + Vt_new.size)

    uso_k_10 = calcula_qtd_elementos(U, Sigma_vet, Vt, 10)
    uso_k_100 = calcula_qtd_elementos(U, Sigma_vet, Vt, 100)
    uso_k_500 = calcula_qtd_elementos(U, Sigma_vet, Vt, 500)
   
    ## 1.8
    def get_limite(energia, cumul_Sigma):
        size = len(cumul_Sigma)
    
        for i in range(size):
            if(cumul_Sigma[i] >= cumul_Sigma[size - 1] * 0.8):
                return i
    
    lim_energ = get_limite(0.8, cumul_Sigma)
    

    ### PARTE 2

    ## 2.1
    B_media = np.mean(B, axis=0)
    Bm = B - B_media

    ## 2.2
    S = Bm.T @ Bm
    
    ## 2.3
    w2, V2 = np.linalg.eig(S)

    index = w2.argsort()[::-1] 
    w2 = w2[index]
    V2 = V2[:, index]

    ## 2.4
    valores_sing = np.sqrt(w2)

    ## 2.5
    Sigma_vals_sing = np.diag(valores_sing)
    Sigma_inv = np.linalg.inv(Sigma_vals_sing)

    ## 2.6
    U2_10 = Bm[:10, :] @ V2 @ Sigma_inv
    imgs2_10 = reconstrucao_aproximada(U2_10, Sigma_vals_sing, V2.T, 200)
    

    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    answers = {
        "1.1.1" : (U, 'U'),
        "1.1.2" : (Sigma_vet, 'Sigma_vet'),
        "1.1.3" : (Vt, 'Vt'),
        "1.2" : (Sigma, "Sigma"),
        "1.3" : (imgReconst_3, 'imgReconst_3'),
        "1.4.1" : (log_Sigma, 'log_Sigma'),
        "1.4.2" : (cumul_Sigma, 'cumul_Sigma'),
        "1.5" : (rmseReconst_3, 'rmseReconst_3'),
        "1.6.1" : (imgReconst_10, 'imgReconst_10'),
        "1.6.2" : (rmseReconst_10, 'rmseReconst_10'),
        "1.6.3" : (imgReconst_100, 'imgReconst_100'),
        "1.6.4" : (rmseReconst_100, 'rmseReconst_100'),
        "1.6.5" : (imgReconst_500, 'imgReconst_500'),
        "1.6.6" : (rmseReconst_500, 'rmseReconst_500'),
        "1.7.1" : (uso_k_10, 'uso_k_10'),
        "1.7.2" : (uso_k_100, 'uso_k_100'),
        "1.7.3" : (uso_k_500, 'uso_k_500'),
        "1.8" : (lim_energ, 'lim_energ'),
        "2.1.1" : (B_media, 'B_media'),
        "2.1.2" : (Bm, 'Bm'),
        "2.2" : (S, 'S'),
        "2.3.1" : (w2, 'w2'),
        "2.3.2" : (V2, 'V2'),
        "2.4" : (valores_sing, 'valores_sing'),
        "2.5.1" : (Sigma_vals_sing, 'Sigma_vals_sing'),
        "2.5.2" : (Sigma_inv, 'Sigma_inv'),
        "2.6.1" :  (U2_10, 'U2_10'),
        "2.6.2" : (imgs2_10, 'imgs2_10')
    }
    return answers
    ##########################################################################

