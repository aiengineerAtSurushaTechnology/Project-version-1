import site

import sys
#sys.path.insert(0,"C:/Users/Hp/AppData/Local/Programs/Python/Python311/Lib/site-packages")
#sys.path.insert(0,"C:/Users/Acer/AppData/Local/Programs/Python/Python311/Lib/site-site-packages")
import numpy
from rdkit import Chem
def main():
    #print(constants.liter)
    m = Chem.MolFromSmiles('Cc1ccccc1')
    print(' Calling python script success... ')
    arr = numpy.array([1, 2, 3, 4, 5])
    print("numpy array")
    print(arr)
    #pdb.set_trace()
    a = 1 + 1

    print('a = 1+1 = %d' %a)
    return "Abhijeet Hello"

if __name__ == "__main__":
    print(" site-packages ")
    print(site.getsitepackages())
    main()
    print("calling __main__ success...")
