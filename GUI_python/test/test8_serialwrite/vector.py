#vector
from tkinter import * # importiamo tutta la lib Tkinter
import time # lib per i ritardi

window = Tk() #creo la finestra
window.title('Interfaccia grafica') #metto il titolo alla finestra
window.geometry("1259x648") #dimensioni per la finestra
window.configure(bg = "#ffffff") #background bianco
canvas = Canvas( #creiamo un'area speciale per disegnare
    window, #passiamo il master
    bg = "#ffffff",
    height = 648,
    width = 1259,
    bd = 0, #border width
    highlightthickness = 0,
    relief = "ridge") #stile simile al tasto

canvas.place(x = 0, y = 0) #dall'angolo in alto a sx



#etichette per gli assi
v=canvas.create_text( 
    575.0, 324.0,
    text = "V(t)",
    fill = "#000000",
    font = ("None", int(12.0)))
t=canvas.create_text(
    1099.0, 551.5,
    text = "t",
    fill = "#000000",
    font = ("None", int(12.0)))



# Chart

canvas.create_line(canvas.coords(v)[0]-10, canvas.coords(t)[1], canvas.coords(t)[0]-20, canvas.coords(t)[1], arrow='last'  )
canvas.create_line(canvas.coords(v)[0], canvas.coords(t)[1]+10 , canvas.coords(v)[0], canvas.coords(v)[1]+20, arrow='last')

datax=[0, 0]
data_m=[0, 0]
data_s=[0, 0]
rangemax=200
passo=(canvas.coords(t)[0]-20-canvas.coords(v)[0]-10)/rangemax

for i in range(0,rangemax+1):
    datax.insert(i,int(canvas.coords(v)[0]-10+i*passo))
    data_m.insert(i,canvas.coords(t)[1])
    data_s.insert(i,canvas.coords(t)[1])
#    data_m.insert(i,500)
#    data_s.insert(i,300)
    
del datax[rangemax+1:]
del data_s[rangemax+1:]
del data_m[rangemax+1:]

print(datax)
print(data_s)
print(data_m)
