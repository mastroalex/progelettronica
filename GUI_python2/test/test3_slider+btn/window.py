from tkinter import *
import time

bottone=True



def btn_clicked():
    global bottone
    print("Button Clicked")
    if (bottone):
        b0.config(image = img1)
        print("C1")
    elif (bottone==False):
        b0.config(image = img0)
        print("C0")
        spinza.set(90)
        sroll.set(90)
    bottone=not(bottone)
    print(bottone)


def spinza_changed(event):  
    time.sleep(0.1)
    print("P"+str(spinza.get()))
    
def sroll_changed(event):  
    time.sleep(0.1)
    print("R"+str(sroll.get()))


window = Tk()
window.title('Interfaccia Grafica')
window.geometry("1259x648")
window.configure(bg = "#ffffff")
canvas = Canvas(
    window,
    bg = "#ffffff",
    height = 648,
    width = 1259,
    bd = 0,
    highlightthickness = 0,
    relief = "ridge")
canvas.place(x = 0, y = 0)

canvas.create_text(
    622.0, 115.0,
    text = "ROLL",
    fill = "#000000",
    font = ("None", int(24.0)))


canvas.create_rectangle(
    553, 140, 553+137, 140+62,
    fill = "#dedede",
    outline = "")


canvas.create_rectangle(
    977, 140, 977+137, 140+62,
    fill = "#dedede",
    outline = "")


canvas.create_rectangle(
    765, 140, 765+137, 140+62,
    fill = "#dedede",
    outline = "")

win = Frame(window)

win.pack(side =LEFT,fill=None, expand=False)

spinza = Scale(win, from_=0, to=180,orient=HORIZONTAL,command=spinza_changed)
spinza.pack(side=BOTTOM, padx=120, ipadx=60)
spinza.set(90)

sroll = Scale(win, from_=0, to=180,orient=HORIZONTAL,command=sroll_changed)
sroll.pack(side=BOTTOM, pady=100,  ipadx=60)
sroll.set(90)

img0 = PhotoImage(file = f"img0.png")
img1 = PhotoImage(file = f"img1.png")
b0 = Button(
    image = img0,
    borderwidth = 0,
    highlightthickness = 0,
    command = btn_clicked,
    relief = "flat")

b0.place(
    x = 143, y = 79,
    width = 180,
    height = 123)

canvas.create_text(
    621.5, 172.0,
    text = "0 °",
    fill = "#000000",
    font = ("None", int(24.0)))

canvas.create_text(
    832.0, 169.0,
    text = "0",
    fill = "#000000",
    font = ("None", int(24.0)))

canvas.create_text(
    1045.5, 170.5,
    text = "0 °C",
    fill = "#000000",
    font = ("None", int(24.0)))


canvas.create_rectangle(
    553, 311, 553+561, 311+255,
    fill = "#ffffff",
    outline = "")

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

canvas.create_text(
    834.5, 115.0,
    text = "BPM",
    fill = "#000000",
    font = ("None", int(24.0)))

canvas.create_text(
    1045.5, 115.0,
    text = "TEMP",
    fill = "#000000",
    font = ("None", int(24.0)))



# Chart

canvas.create_line(canvas.coords(v)[0]-10, canvas.coords(t)[1], canvas.coords(t)[0]-20, canvas.coords(t)[1], arrow='last'  )
canvas.create_line(canvas.coords(v)[0], canvas.coords(t)[1]+10 , canvas.coords(v)[0], canvas.coords(v)[1]+20, arrow='last')



window.resizable(False, False)
window.mainloop()

