from tkinter import *


def btn_clicked():
    print("Button Clicked")
    canvas.itemconfigure(b, text="a")

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


canvas.create_rectangle(
    553, 140, 553+137, 140+62,
    fill = "#ded9d9",
    outline = "")


canvas.create_rectangle(
    977, 140, 977+137, 140+62,
    fill = "#c4c4c4",
    outline = "")


canvas.create_rectangle(
    765, 140, 765+137, 140+62,
    fill = "#c4c4c4",
    outline = "")

img0 = PhotoImage(file = f"img0.png")
b0 = Button(
    image = img0,
    borderwidth = 0,
    highlightthickness = 0,
    command = btn_clicked,
    relief = "flat")

b0.place(
    x = 245, y = 79,
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

b=canvas.create_text(
    1045.5, 170.5,
    text = "0 °C",
    fill = "#000000",
    font = ("None", int(24.0)))

window.resizable(False, False)
window.mainloop()
