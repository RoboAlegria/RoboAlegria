#coding: latin1
#''' módulo que comunicacao com o robo '''

import serial
import time

con = serial.Serial('/dev/ttyUSB0',9600)

#função que passa o comando mov concatenado com um pipe e valor do movimento
def movimentar_bracos(movimento):
    cmd = 'mov|'+movimento
    con.write(cmd.encode())
    time.sleep(3)
