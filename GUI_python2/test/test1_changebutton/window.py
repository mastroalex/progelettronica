from tkinter import *


def btn_clicked():
    print("Button Clicked")
    b0.config(image = img1)


window = Tk()

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

img0 = PhotoImage(file = f"img0.png")
img1 = PhotoImage(file = f"img1.png")
b0 = Button(
    image = img0,
    borderwidth = 0,
    highlightthickness = 0,
    command = btn_clicked,
    relief = "flat")

b0.place(
    x = 263, y = 247,
    width = 180,
    height = 123)

canvas.create_text(
    555.5, 340.0,
    text = "0 °",
    fill = "#000000",
    font = ("None", int(24.0)))

canvas.create_text(
    766.0, 337.0,
    text = "0",
    fill = "#000000",
    font = ("None", int(24.0)))

canvas.create_text(
    979.5, 338.5,
    text = "0 °C",
    fill = "#000000",
    font = ("None", int(24.0)))

window.resizable(False, False)
window.mainloop()
