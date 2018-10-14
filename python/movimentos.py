from enum import Enum

#class que guarda os códigos utilizados para os movimentos programados do Arduino
class Movimento(Enum):
    LEVANTAR_BRACO_ESQUERDO = 10
    LEVANTAR_BRACO_DIREITO = 20
    LEVANTAR_DOIS_BRACOS = 30
    ABAIXAR_DOIS_BRACOS = 40
    PRA_CIMA_PRA_BAIXO_DOIS_BRACOS = 50
    PRA_FRENTE_PRA_TRAS_DOIS_BRACOS = 60
    GIRAR_OS_BRACOS = 80
    ACENAR = 90
