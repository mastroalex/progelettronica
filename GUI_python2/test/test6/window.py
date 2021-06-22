from tkinter import * # importiamo tutta la lib Tkinter
import serial # lib per la comunicazione seriale
import time # lib per i ritardi


bottone=True #variabile di stato per il bottone (switch)(True=automatico, False=manuale)
porta='/dev/tty.usbserial-146140'

def btn_clicked(): #fz per aggiornare il pulsante, viene richiamata quando cliccato
    global bottone #utilizzare variabili globali
    # print("Button Clicked") 
    if (bottone): #siamo in controllo automatico
        b0.config(image = img1) #aggiorna l'imm in rosso
        print("C1") #per cambiare modalità su arduino
    elif (bottone==False): #se siamo in controllo manuale
        b0.config(image = img0) #aggiorna l'imm in grigio
        print("C0") #per cambiare modalità su arduino
        #reset degli slider
        spinza.set(90)
        sroll.set(90)
    bottone=not(bottone) #cambia lo stato quando viene premuto il pulsante
    # print(bottone)


def spinza_changed(event):  #viene attivata quando varia lo slider spinza
    time.sleep(0.1) #aspettano 100 ms per evitare di stampare tutti i valori dello slider che si muove
    print("P"+str(spinza.get())) #stampa codificata
    
def sroll_changed(event):  #viene attivata quando varia lo slider sroll
    time.sleep(0.1) #aspettano 100 ms per evitare di stampare tutti i valori dello slider che si muove
    print("R"+str(sroll.get())) #stampa codificata

#inizializzo la seriale 
arduino = serial.Serial(porta, 9600)
time.sleep(1)
#print("pronto a ricevere")

indice=1
def arduinoreceive(): #funzione per ricevere
    global a
    canvas.delete(a)
    global indice
    testo= arduino.readline() #legge la riga
    testo=testo.rstrip() #elimina i caratter '\r\n'
    testo=testo.decode("utf-8")  #utilizza la codifica corretta
    print(testo)
    canvas.itemconfigure(text,text=str(testo)) #aggiorna l'etichetta per il debug
    window.after(200, arduinoreceive) #quando cambiano le etichette richiama la funzione creando un loop
    #iniziamo la decodifica
    if testo[0]=="T":
        print("Temperatura = "+testo.replace('T', ''))
        canvas.itemconfigure(temp_label,text=testo.replace('T', '')+" ° C")
    if testo[0]=="A":
        print("Angolo = "+testo.replace('A', ''))
        canvas.itemconfigure(roll_label,text=testo.replace('A', '')+" °")
    if testo[0]=="B":
        print("Bpm = "+testo.replace('B', ''))
        canvas.itemconfigure(bpm_label,text=testo.replace('B', ''))
    if testo[0]=="M" or testo[0]=="S":
        if testo[0]=="M":
            data_m[indice]=mappa(testo.replace('M', ''))
            print(data_m[indice])
            print(indice)
        if testo[0]=="S":
            data_s[indice]=mappa(testo.replace('S', ''))
        a=canvas.create_line(datax[0],data_m[0], datax[1], data_m[1], datax[2], data_m[2], datax[3], data_m[3]  )
        indice+=1
        if indice==200:
            indice=1

    
def mappa(valore):
    dato=canvas.coords(t)[1]-(canvas.coords(t)[1]-canvas.coords(v)[1])*int(valore)/1023
    return int(dato)



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

a=canvas.create_line(0,0,1,1)

roll=canvas.create_text( #etichetta "ROLL"
    622.0, 115.0,
    text = "ROLL",
    fill = "#000000",
    font = ("None", int(24.0)))
canvas.create_text( #etichetta "BPM"
    834.5, 115.0,
    text = "BPM",
    fill = "#000000",
    font = ("None", int(24.0)))
canvas.create_text( #etichetta "TEMP"
    1045.5, 115.0,
    text = "TEMP",
    fill = "#000000",
    font = ("None", int(24.0)))

text=canvas.create_text( #etichetta per il DEBUG della seriale
    100, 600,
    text = "DEBUG",
    fill = "#000000",
    font = ("None", int(24.0)))


canvas.create_rectangle( #display di sfondo per i valori
    553, 140, 553+137, 140+62,
    fill = "#dedede",
    outline = "") #bordo

canvas.create_rectangle( #display di sfondo per i valori
    977, 140, 977+137, 140+62,
    fill = "#dedede",
    outline = "") #bordo

canvas.create_rectangle(
    765, 140, 765+137, 140+62, #display di sfondo per i valori
    fill = "#dedede",
    outline = "") #bordo


#creo gli slider
# win = Frame(window,bg="blue") creiamo prima il contenitore
win = Frame(window)
win.pack(side =LEFT, expand=False)

spinza = Scale(win, from_=0, to=180,orient=HORIZONTAL,command=spinza_changed) #creiamo il widget con Scale
spinza.pack(side=BOTTOM, padx=120, ipadx=60) #allineiamo lo slider e lo allarghiamo
spinza.set(90) #mettiamo l'indicatore al centro
#creiamo il secondo slider
sroll = Scale(win, from_=0, to=180,orient=HORIZONTAL,command=sroll_changed)
sroll.pack(side=BOTTOM, pady=100,  ipadx=60)
sroll.set(90)

#carico le img
img0 = PhotoImage(file = f"img0.png")
img1 = PhotoImage(file = f"img1.png")
#creo il bottone per il controllo
b0 = Button(
    image = img0,
    borderwidth = 0,
    highlightthickness = 0,
    command = btn_clicked,
    relief = "flat")
#posiziono il bottone per il controllo
b0.place(
    x = 143, y = 79,
    width = 180,
    height = 123)

roll_label=canvas.create_text( #label per Roll
    621.5, 172.0,
    text = "0 °",
    fill = "#000000",
    font = ("None", int(24.0)))

bpm_label=canvas.create_text( #label per i Bpm
    832.0, 169.0,
    text = "0",
    fill = "#000000",
    font = ("None", int(24.0)))

temp_label=canvas.create_text( #label per la Temp
    1045.5, 170.5,
    text = "0 °C",
    fill = "#000000",
    font = ("None", int(24.0)))

grafico=canvas.create_rectangle( #sfondo per il grafico 
    553, 311, 553+561, 311+255,
    fill = "#dedede",
    outline = "")

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
passo=(canvas.coords(t)[0]-20-canvas.coords(v)[0]-10)/200

for i in range(0,200):
    datax.insert(i,int(canvas.coords(v)[0]-10+i*passo))
    print(datax)
#     data_m.insert(i,canvas.coords(t)[1])
#     data_s.insert(i,canvas.coords(t)[1])
    data_m.insert(i,100)
    data_s.insert(i,300)
    
del datax[201:]
del data_s[201:]
del data_m[201:]

arduinoreceive()
window.resizable(False, False)
window.mainloop()

