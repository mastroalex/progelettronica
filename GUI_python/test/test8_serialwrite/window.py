from tkinter import * # importiamo tutta la lib Tkinter
import serial # lib per la comunicazione seriale
import time # lib per i ritardi

bottone=True #variabile di stato per il bottone (switch)(True=automatico, False=manuale)
#porta='/dev/tty.usbserial-146120'
porta='/dev/cu.HC-05-SerialPort'

datax=[565, 567, 569, 572, 574, 577, 579, 582, 584, 587, 589, 592, 594, 597, 599, 602, 604, 606, 609, 611,
       614, 616, 619, 621, 624, 626, 629, 631, 634, 636, 639, 641, 644, 646, 648, 651, 653, 656, 658, 661,
       663, 666, 668, 671, 673, 676, 678, 681, 683, 686, 688, 690, 693, 695, 698, 700, 703, 705, 708, 710,
       713, 715, 718, 720, 723, 725, 728, 730, 732, 735, 737, 740, 742, 745, 747, 750, 752, 755, 757, 760,
       762, 765, 767, 770, 772, 774, 777, 779, 782, 784, 787, 789, 792, 794, 797, 799, 802, 804, 807, 809,
       812, 814, 816, 819, 821, 824, 826, 829, 831, 834, 836, 839, 841, 844, 846, 849, 851, 853, 856, 858,
       861, 863, 866, 868, 871, 873, 876, 878, 881, 883, 886, 888, 891, 893, 895, 898, 900, 903, 905, 908,
       910, 913, 915, 918, 920, 923, 925, 928, 930, 933, 935, 937, 940, 942, 945, 947, 950, 952, 955, 957,
       960, 962, 965, 967, 970, 972, 975, 977, 979, 982, 984, 987, 989, 992, 994, 997, 999, 1002, 1004, 1007,
       1009, 1012, 1014, 1017, 1019, 1021, 1024, 1026, 1029, 1031, 1034, 1036, 1039, 1041, 1044, 1046, 1049,
       1051, 1054, 1056, 1059]
data_m=[551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5]

data_s=[551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5, 551.5,
        551.5, 551.5, 551.5, 551.5, 551.5, 551.5]



def btn_clicked(): #fz per aggiornare il pulsante, viene richiamata quando cliccato
    global bottone #utilizzare variabili globali
    # print("Button Clicked") 
    if (bottone): #siamo in controllo automatico5
        b0.config(image = img1) #aggiorna l'imm in rosso
        print("C1") #per cambiare modalità su arduino
        arduino.write(b'C1\r\n')
    elif (bottone==False): #se siamo in controllo manuale
        b0.config(image = img0) #aggiorna l'imm in grigio
        print("C0") #per cambiare modalità su arduino
        arduino.write(b'C0\r\n')
#reset degli slider
        spinza.set(90)
        sroll.set(90)
    bottone=not(bottone) #cambia lo stato quando viene premuto il pulsante
    # print(bottone)


def spinza_changed(event):  #viene attivata quando varia lo slider spinza
    time.sleep(0.3) #aspettano 100 ms per evitare di stampare tutti i valori dello slider che si muove
    print("P"+str(spinza.get())) #stampa codificata
    if (bottone==False):
        arduino.write(bytes("P"+str(spinza.get())+"\r\n", 'utf-8'))
    
def sroll_changed(event):  #viene attivata quando varia lo slider sroll
    time.sleep(0.3) #aspettano 100 ms per evitare di stampare tutti i valori dello slider che si muove
    print("R"+str(sroll.get())) #stampa codificata
    if (bottone==False):
        arduino.write(bytes("R"+str(sroll.get())+"\r\n", 'utf-8'))

#inizializzo la seriale 
arduino = serial.Serial(porta, 9600)
time.sleep(1)
#print("pronto a ricevere")

indicem=0
indices=0

def arduinoreceive(): #funzione per ricevere
    global a
    global b
    canvas.delete(a)
    canvas.delete(b)
    global indicem
    global indices
    testo= arduino.readline() #legge la riga
    testo=testo.rstrip() #elimina i caratter '\r\n'
    testo=testo.decode("utf-8")  #utilizza la codifica corretta
    #print(testo)
    canvas.itemconfigure(grafico,fill='white') 
    canvas.itemconfigure(text,text=str(testo)) #aggiorna l'etichetta per il debug
    window.after(50, arduinoreceive) #quando cambiano le etichette richiama la funzione creando un loop
    #iniziamo la decodifica
    if testo[0]=="T":
     #   print("Temperatura = "+testo.replace('T', ''))
        canvas.itemconfigure(temp_label,text=testo.replace('T', '')+" ° C")
    if testo[0]=="A":
     #   print("Angolo = "+testo.replace('A', ''))
        canvas.itemconfigure(roll_label,text=testo.replace('A', '')+" °")
    if testo[0]=="B":
     #   print("Bpm = "+testo.replace('B', ''))
        canvas.itemconfigure(bpm_label,text=testo.replace('B', ''))
    if testo[0]=="M":
        data_m[indicem]=mappa(testo.replace('M', ''))
     #   print(f"data_m{indicem}]="+str(data_m[indicem]))
      #  print(indicem)
        indicem+=1
    if testo[0]=="S":
        data_s[indices]=mappa(testo.replace('S', ''))
        indices+=1
    a=canvas.create_line(datax[0], data_m[0], 
datax[1], data_m[1], datax[2], data_m[2], datax[3], data_m[3], datax[4], data_m[4], datax[5], data_m[5], datax[6], data_m[6], datax[7], data_m[7], datax[8], data_m[8], datax[9], data_m[9], datax[10], data_m[10], 
datax[11], data_m[11], datax[12], data_m[12], datax[13], data_m[13], datax[14], data_m[14], datax[15], data_m[15], datax[16], data_m[16], datax[17], data_m[17], datax[18], data_m[18], datax[19], data_m[19], datax[20], data_m[20], 
datax[21], data_m[21], datax[22], data_m[22], datax[23], data_m[23], datax[24], data_m[24], datax[25], data_m[25], datax[26], data_m[26], datax[27], data_m[27], datax[28], data_m[28], datax[29], data_m[29], datax[30], data_m[30], 
datax[31], data_m[31], datax[32], data_m[32], datax[33], data_m[33], datax[34], data_m[34], datax[35], data_m[35], datax[36], data_m[36], datax[37], data_m[37], datax[38], data_m[38], datax[39], data_m[39], datax[40], data_m[40], 
datax[41], data_m[41], datax[42], data_m[42], datax[43], data_m[43], datax[44], data_m[44], datax[45], data_m[45], datax[46], data_m[46], datax[47], data_m[47], datax[48], data_m[48], datax[49], data_m[49], datax[50], data_m[50], 
datax[51], data_m[51], datax[52], data_m[52], datax[53], data_m[53], datax[54], data_m[54], datax[55], data_m[55], datax[56], data_m[56], datax[57], data_m[57], datax[58], data_m[58], datax[59], data_m[59], datax[60], data_m[60], 
datax[61], data_m[61], datax[62], data_m[62], datax[63], data_m[63], datax[64], data_m[64], datax[65], data_m[65], datax[66], data_m[66], datax[67], data_m[67], datax[68], data_m[68], datax[69], data_m[69], datax[70], data_m[70], 
datax[71], data_m[71], datax[72], data_m[72], datax[73], data_m[73], datax[74], data_m[74], datax[75], data_m[75], datax[76], data_m[76], datax[77], data_m[77], datax[78], data_m[78], datax[79], data_m[79], datax[80], data_m[80], 
datax[81], data_m[81], datax[82], data_m[82], datax[83], data_m[83], datax[84], data_m[84], datax[85], data_m[85], datax[86], data_m[86], datax[87], data_m[87], datax[88], data_m[88], datax[89], data_m[89], datax[90], data_m[90], 
datax[91], data_m[91], datax[92], data_m[92], datax[93], data_m[93], datax[94], data_m[94], datax[95], data_m[95], datax[96], data_m[96], datax[97], data_m[97], datax[98], data_m[98], datax[99], data_m[99], datax[100], data_m[100],
datax[101], data_m[101], datax[102], data_m[102], datax[103], data_m[103], datax[104], data_m[104], datax[105], data_m[105], datax[106], data_m[106], datax[107], data_m[107], datax[108], data_m[108], datax[109], data_m[109], datax[110], data_m[110], 
datax[111], data_m[111], datax[112], data_m[112], datax[113], data_m[113], datax[114], data_m[114], datax[115], data_m[115], datax[116], data_m[116], datax[117], data_m[117], datax[118], data_m[118], datax[119], data_m[119], datax[120], data_m[120], 
datax[121], data_m[121], datax[122], data_m[122], datax[123], data_m[123], datax[124], data_m[124], datax[125], data_m[125], datax[126], data_m[126], datax[127], data_m[127], datax[128], data_m[128], datax[129], data_m[129], datax[130], data_m[130], 
datax[131], data_m[131], datax[132], data_m[132], datax[133], data_m[133], datax[134], data_m[134], datax[135], data_m[135], datax[136], data_m[136], datax[137], data_m[137], datax[138], data_m[138], datax[139], data_m[139], datax[140], data_m[140], 
datax[141], data_m[141], datax[142], data_m[142], datax[143], data_m[143], datax[144], data_m[144], datax[145], data_m[145], datax[146], data_m[146], datax[147], data_m[147], datax[148], data_m[148], datax[149], data_m[149], datax[150], data_m[150], 
datax[151], data_m[151], datax[152], data_m[152], datax[153], data_m[153], datax[154], data_m[154], datax[155], data_m[155], datax[156], data_m[156], datax[157], data_m[157], datax[158], data_m[158], datax[159], data_m[159], datax[160], data_m[160], 
datax[161], data_m[161], datax[162], data_m[162], datax[163], data_m[163], datax[164], data_m[164], datax[165], data_m[165], datax[166], data_m[166], datax[167], data_m[167], datax[168], data_m[168], datax[169], data_m[169], datax[170], data_m[170], 
datax[171], data_m[171], datax[172], data_m[172], datax[173], data_m[173], datax[174], data_m[174], datax[175], data_m[175], datax[176], data_m[176], datax[177], data_m[177], datax[178], data_m[178], datax[179], data_m[179], datax[180], data_m[180], 
datax[181], data_m[181], datax[182], data_m[182], datax[183], data_m[183], datax[184], data_m[184], datax[185], data_m[185], datax[186], data_m[186], datax[187], data_m[187], datax[188], data_m[188], datax[189], data_m[189], datax[190], data_m[190], 
datax[191], data_m[191], datax[192], data_m[192], datax[193], data_m[193], datax[194], data_m[194], datax[195], data_m[195], datax[196], data_m[196], datax[197], data_m[197], datax[198], data_m[198], datax[199], data_m[199], datax[200], data_m[200],fill='red')
    b=canvas.create_line(datax[0], data_s[0], 
datax[1], data_s[1], datax[2], data_s[2], datax[3], data_s[3], datax[4], data_s[4], datax[5], data_s[5], datax[6], data_s[6], datax[7], data_s[7], datax[8], data_s[8], datax[9], data_s[9], datax[10], data_s[10], 
datax[11], data_s[11], datax[12], data_s[12], datax[13], data_s[13], datax[14], data_s[14], datax[15], data_s[15], datax[16], data_s[16], datax[17], data_s[17], datax[18], data_s[18], datax[19], data_s[19], datax[20], data_s[20], 
datax[21], data_s[21], datax[22], data_s[22], datax[23], data_s[23], datax[24], data_s[24], datax[25], data_s[25], datax[26], data_s[26], datax[27], data_s[27], datax[28], data_s[28], datax[29], data_s[29], datax[30], data_s[30], 
datax[31], data_s[31], datax[32], data_s[32], datax[33], data_s[33], datax[34], data_s[34], datax[35], data_s[35], datax[36], data_s[36], datax[37], data_s[37], datax[38], data_s[38], datax[39], data_s[39], datax[40], data_s[40], 
datax[41], data_s[41], datax[42], data_s[42], datax[43], data_s[43], datax[44], data_s[44], datax[45], data_s[45], datax[46], data_s[46], datax[47], data_s[47], datax[48], data_s[48], datax[49], data_s[49], datax[50], data_s[50], 
datax[51], data_s[51], datax[52], data_s[52], datax[53], data_s[53], datax[54], data_s[54], datax[55], data_s[55], datax[56], data_s[56], datax[57], data_s[57], datax[58], data_s[58], datax[59], data_s[59], datax[60], data_s[60], 
datax[61], data_s[61], datax[62], data_s[62], datax[63], data_s[63], datax[64], data_s[64], datax[65], data_s[65], datax[66], data_s[66], datax[67], data_s[67], datax[68], data_s[68], datax[69], data_s[69], datax[70], data_s[70], 
datax[71], data_s[71], datax[72], data_s[72], datax[73], data_s[73], datax[74], data_s[74], datax[75], data_s[75], datax[76], data_s[76], datax[77], data_s[77], datax[78], data_s[78], datax[79], data_s[79], datax[80], data_s[80], 
datax[81], data_s[81], datax[82], data_s[82], datax[83], data_s[83], datax[84], data_s[84], datax[85], data_s[85], datax[86], data_s[86], datax[87], data_s[87], datax[88], data_s[88], datax[89], data_s[89], datax[90], data_s[90], 
datax[91], data_s[91], datax[92], data_s[92], datax[93], data_s[93], datax[94], data_s[94], datax[95], data_s[95], datax[96], data_s[96], datax[97], data_s[97], datax[98], data_s[98], datax[99], data_s[99], datax[100], data_s[100], 
datax[101], data_s[101], datax[102], data_s[102], datax[103], data_s[103], datax[104], data_s[104], datax[105], data_s[105], datax[106], data_s[106], datax[107], data_s[107], datax[108], data_s[108], datax[109], data_s[109], datax[110], data_s[110], 
datax[111], data_s[111], datax[112], data_s[112], datax[113], data_s[113], datax[114], data_s[114], datax[115], data_s[115], datax[116], data_s[116], datax[117], data_s[117], datax[118], data_s[118], datax[119], data_s[119], datax[120], data_s[120], 
datax[121], data_s[121], datax[122], data_s[122], datax[123], data_s[123], datax[124], data_s[124], datax[125], data_s[125], datax[126], data_s[126], datax[127], data_s[127], datax[128], data_s[128], datax[129], data_s[129], datax[130], data_s[130], 
datax[131], data_s[131], datax[132], data_s[132], datax[133], data_s[133], datax[134], data_s[134], datax[135], data_s[135], datax[136], data_s[136], datax[137], data_s[137], datax[138], data_s[138], datax[139], data_s[139], datax[140], data_s[140], 
datax[141], data_s[141], datax[142], data_s[142], datax[143], data_s[143], datax[144], data_s[144], datax[145], data_s[145], datax[146], data_s[146], datax[147], data_s[147], datax[148], data_s[148], datax[149], data_s[149], datax[150], data_s[150], 
datax[151], data_s[151], datax[152], data_s[152], datax[153], data_s[153], datax[154], data_s[154], datax[155], data_s[155], datax[156], data_s[156], datax[157], data_s[157], datax[158], data_s[158], datax[159], data_s[159], datax[160], data_s[160], 
datax[161], data_s[161], datax[162], data_s[162], datax[163], data_s[163], datax[164], data_s[164], datax[165], data_s[165], datax[166], data_s[166], datax[167], data_s[167], datax[168], data_s[168], datax[169], data_s[169], datax[170], data_s[170], 
datax[171], data_s[171], datax[172], data_s[172], datax[173], data_s[173], datax[174], data_s[174], datax[175], data_s[175], datax[176], data_s[176], datax[177], data_s[177], datax[178], data_s[178], datax[179], data_s[179], datax[180], data_s[180], 
datax[181], data_s[181], datax[182], data_s[182], datax[183], data_s[183], datax[184], data_s[184], datax[185], data_s[185], datax[186], data_s[186], datax[187], data_s[187], datax[188], data_s[188], datax[189], data_s[189], datax[190], data_s[190], 
datax[191], data_s[191], datax[192], data_s[192], datax[193], data_s[193], datax[194], data_s[194], datax[195], data_s[195], datax[196], data_s[196], datax[197], data_s[197], datax[198], data_s[198], datax[199], data_s[199], datax[200], data_s[200])
    if indicem==rangemax:
        indicem=0
    if indices==rangemax:
        indices=0
# fine arduino receive

def mappa(valore):
    dato=canvas.coords(t)[1]-(canvas.coords(t)[1]-canvas.coords(v)[1])*abs(int(valore))/1023
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
b=canvas.create_line(0,0,1,1)

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
sroll = Scale(win, from_=-90, to=90,orient=HORIZONTAL,command=sroll_changed)
sroll.pack(side=BOTTOM, pady=100,  ipadx=60)
sroll.set(0)

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

# datax=[0, 0]
# data_m=[0, 0]
# data_s=[0, 0]
rangemax=200
# passo=(canvas.coords(t)[0]-20-canvas.coords(v)[0]-10)/rangemax
# 
# for i in range(0,rangemax+1):
#     datax.insert(i,int(canvas.coords(v)[0]-10+i*passo))
#     print(datax)
#     data_m.insert(i,canvas.coords(t)[1])
#     data_s.insert(i,canvas.coords(t)[1])
# #    data_m.insert(i,500)
# #    data_s.insert(i,300)
#     
# del datax[rangemax+1:]
# del data_s[rangemax+1:]
# del data_m[rangemax+1:]

arduinoreceive()
window.resizable(False, False)
window.mainloop()

