nome = ""
matricula = None

def EP_answers():
    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    import numpy as np
    np.random.seed(1)
    inversa, pseudo_inversa, QR, substituicao, retrosubstituicao, \
    positiva_definida, simetrica, cholesky = [None]*8
    #########################################################################

    ## 1.1
    def inversa(X, y):
        XTX = X.T @ X
        XTX_inv = np.linalg.inv(XTX)

        return XTX_inv @ (X.T @ y)

    ## 1.2
    def pseudo_inversa(X, y):
        U, Sigma, Vt = np.linalg.svd(X, full_matrices=False)

        pseudo_inv = Vt.T @ np.diag((1 / Sigma)) @ U.T

        return pseudo_inv @ y

    ## 1.3
    def QR(X, y):
        Q, R = np.linalg.qr(X)

        return np.linalg.inv(R) @ Q.T @ y

    ## 1.4
    def substituicao(L, b):
        return np.linalg.inv(L) @ b

    def retrosubstituicao(Lt, C):
        return np.linalg.inv(Lt) @ C

    def positiva_definida(X):
        return np.all(np.linalg.eigvals(X) > 0)

    def simetrica(X):
        return np.allclose(X, X.T)

    def cholesky(X, y):
        assert positiva_definida(X.T @ X), 'A matriz de entrada não é positiva definida'
        assert simetrica(X.T @ X), 'A matriz de entrada não é simétrica'

        L = np.linalg.cholesky(X.T @ X)
        C = substituicao(L, X.T @ y)

        return retrosubstituicao(L.T, C)

    ################### NÃO ALTERE DENTRO DA SEÇÃO ABAIXO ###################
    answers = {
        "1.1.1" : inversa,
        "1.2" : pseudo_inversa,
        "1.3" : QR,
        "1.4.1" : substituicao,
        "1.4.2" : retrosubstituicao,
        "1.4.3" : positiva_definida,
        "1.4.4" : simetrica,
        "1.4.5" : cholesky
    }
    return answers
    ##########################################################################
