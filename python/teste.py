#coding: latin-1
#'''código de para testar o robo'''
import robo
import movimentos

print("Lenvantar braço direito")
movimentar_bracos(Movimento.LEVANTAR_BRACO_DIREITO)
print("Levantar braço levantar braco esquerdo")
movimentar_bracos(Movimento.LEVANTAR_BRACO_ESQUERDO)
print("Abaixar os dois braços")
movimentar_bracos(Movimento.ABAIXAR_DOIS_BRACOS)
print("Acenar")
movimentar_bracos(Movimento.ACENAR)
