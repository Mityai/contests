# save this file as ......| test1.py
# run this file this way..| python  test1.py
import easygui as eg
import sys

while 1:
    #title = "Message from test1.py"
    #eg.msgbox("Hello, world!", title)

    msg ="What is your favorite flavor?"
    title = "Ice Cream Survey"
    choices = ["Vanilla", "Chocolate", "Strawberry", "Rocky Road"]
    choice = eg.choicebox(msg, title, choices)

    # note that we convert choice to string, in case
    # the user cancelled the choice, and we got None.
    eg.msgbox("You chose: " + str(choice), "Survey Result")

    msg = "Do you want to continue?"
    title = "Please Confirm"
    if eg.ccbox(msg, title):     # show a Continue/Cancel dialog
        pass  # user chose Continue
    else:
        sys.exit(0)           # user chose Cancel
