def import_inventory():
    pfiles = open("products.txt", "r")
    allp = pfiles.read()
    pfiles.close()

    alist = allp.replace("-","\n").split("\n")

    inv = {}
    for i in alist :
        name = i.split("_")[0].lower()
        number =int(i.split("_")[1])
        if name in inv.keys() :
            inv[name] = inv[name] + number
        else:
            inv[name] = number

    return inv

def sell_product(a):
    in1 = input("Please enter products to sell: ") #take input

    for i in in1.split("-"):
        name = i.split("_")[0].lower()
        number = int(i.split("_")[1])

        if name in a :
            if a[name] < number :
                print("There is not enough", name, "in inventory.")
            elif a[name] > number :
                print(number, name, "sold.")
                a[name] = a[name] - number
            elif a[name] == number :
                print(number, name, "sold.")
                a.pop(name)
        else:
            print(name, "does not exist in inventory.")

def show_remaining(x):
    if len(x) == 0 :
        print("Inventory is empty!")
    else:
        for i in sorted(x):
            print(i, ":", x[i])


products = import_inventory()
decision = ""
while decision != "3":
  print("*---------------------------")
  print("[1] Sell products")
  print("[2] Show remaining inventory")
  print("[3] Terminate")

  decision = input("Please enter your decision: ")
  print("____________________________")
  if decision == "1":
    sell_product(products)
  elif decision == "2":
    show_remaining(products)
  elif decision == "3":
    print("Terminating...")
  else:
    print("Invalid input!")