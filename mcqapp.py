import tkinter as tk
from tkinter import messagebox
import random

questions = [
    {
        'question': "B, D, F, I, L, P, ? (S.S.C)",
        'options': ['(a) R', '(b) S', '(c) T', '(d) U', '(e) None of these']
    },
    {
        'question': "C, Z, F, X, I, V, L, T, O, ?, ?",
        'options': ['(a) O, P', '(b) P, Q', '(c) R, R', '(d) S, R', '(e) None of these']
    },
    {
        'question': "M, N, O, L, R, I, V, ? (BANK P.O)",
        'options': ['(a) A', '(b) E', '(c) F', '(d) H', '(e) Z']
    },
    {
        'question': "A, G, L, P, S, ? (R.R.B)",
        'options': ['(a) U', '(b) W', '(c) X', '(d) Y', '(e) None of these']
    },
    {
        'question': "AI, BJ, CK, ? ( R.R.B)",
        'options': ['(a) DL', '(b) DM', '(c) GH', '(d) LM', '(e) None of these']
    },
    {
        'question': "ATTRIBUTION, TTRIBUTION, RIBUTIO, IBUTI, ? (I.B.P.S)",
        'options': ['(a) IBU', '(b) UT', '(c) UTI', '(d) BUT', '(e) None of these']
    },
    {
        'question': "ABD, DGK, HMS, MTB, SBL, ?",
        'options': ['(a) XKW', '(b) ZAB', '(c) ZKU', '(d) ZKW', '(e) None of these']
    },
    {
        'question': "ajs, gpy, ?, sbk, yhq",
        'options': ['(a) dmv', '(b) mve', '(c) oua', '(d) qzi', '(e) None of these']
    },
    {
        'question': "Z, Y, X, U, T, S, P, O, N, K, ?, ?",
        'options': ['(a) H, G', '(b) H, I', '(c) I, H', '(d) J, I']
    },
]

class MCQApp:
    def __init__(self, master, questions):
        self.master = master
        self.master.title("Random MCQ App")

        self.questions = questions
        self.current_question = None

        self.label_question = tk.Label(master, text="")
        self.label_question.pack()

        self.radio_var = tk.StringVar()
        self.radio_buttons = []

        for i in range(5):
            radio_button = tk.Radiobutton(master, text="", variable=self.radio_var, value=i)
            radio_button.pack()
            self.radio_buttons.append(radio_button)

        self.button_next = tk.Button(master, text="Next", command=self.next_question)
        self.button_next.pack()

        self.load_question()
        
    def load_question(self):
        self.current_question = random.choice(self.questions)

        self.label_question.config(text=self.current_question['question'])

        for i, option in enumerate(self.current_question['options']):
            self.radio_buttons[i].config(text=option)

    def next_question(self):
        selected_option = self.radio_var.get()

        if selected_option == "":
            messagebox.showwarning("Warning", "Please select an option.")
        else:
            messagebox.showinfo("Answer", f"Selected Option: {selected_option}")

            # Clear selection for the next question
            self.radio_var.set("")

            # Load the next question
            self.load_question()

def main():
    root = tk.Tk()

    # Shuffle questions randomly before passing them to the app
    shuffled_questions = random.sample(questions, len(questions))

    app = MCQApp(root, shuffled_questions)
    root.mainloop()

if __name__ == "__main__":
    main()
