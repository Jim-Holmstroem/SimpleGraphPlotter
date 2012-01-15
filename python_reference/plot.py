#!/usr/bin/python

# -*- coding: UTF-8 -*-

from queue import Queue
import math
import cmath
import operator
import re
import sys
import getopt
#TODO-LIST :D

#different log-bases (log2)
#add constants math.pi and math.e
#add functions with multiple arguments fun(,term-(-1),term-(-1),), lambda-functions ?


#KNOWN BUGS
#
# 1.doesn't modulo imaginary numbers (but stills plot the right value but without modulos)
# 2. sin(x)^101 is plotted with both real-imaginary and normal part..
#
# 3.!!!!! BIG ONE!!! -1+1 isn't -2, checkout the readterm ~@219
#
#
#
#


#SUPPORTS
#
# 1. Complex constans in the form "a+bi" where, i = "1i"
# 2. Plotting Complexvalued functions by having a blue (real-part) and red (imag-ppart)
# 3. Conjugate complex functions including operators 
# 4. Plot multiple functions seperated with ';'
# 5. Comparison operators (ex. heavside = (x>0) 
#
#


#TESTS
#
# f = atan(log(sqrt(x)-1))^3 [works]
# f = log(x)^3/5 [works]
# f = +(log(x)) [works]
# f = *(log(x)) [works]
# f = sin(x)*(x>0) [works]
# f = (x>3)+(x>2)+(x>1)+(x>0) [works]
# f = sin(x) > 0 [works]
# f = sin(x);cos(x);-sin(x);-cos(x) [works [works]
# f = (1+1i)**asin(x) 


from Tkinter import *
import tkMessageBox

digit = re.compile("[0-9]")
letter = re.compile("[a-z]")
lettercaps = re.compile("[A-Z]")
funcbegin = re.compile("[a-z(]")

debug = False

version_name = "0.9b"
prgm_name = "Jim-Plotter"

def frange(start,end,step):#NOTE make sure start < end
    return map(lambda x: x*step, range(int(start*1./step),int(end*1./step)))

class ParseException(Exception):
    def __init__(self,value):
        self.value = value
        return
    def __str__(self):
        return repr(self.value)

class EvalException(Exception):
    def __init__(self,value):
        self.value = value
        return
    def __str__(self):
        return repr(self.value)


class Num():
    constant = 0
    def __init__(self,constant):
        self.constant = constant
        return
    def eval(self,x):
        return self.constant

class Variable():
    def eval(self,x):
        return x

class Term():

    def __init__(self,op=None,func=None,unop=None,left=None,right=None):
        self.op = op
        self.func = func
        self.unop = unop
        self.left = left
        self.right = right
        return

    def eval(self,x):
        if(self.op):
            return self.op(self.left.eval(x),self.right.eval(x))
        elif(self.func):
            return self.func(self.left.eval(x))#TODO should these be right or left from a teoretical perspective
        elif(self.unop):
            return self.unop(self.left.eval(x))
        elif(self.left):
            return self.left.eval(x)
        else:
            raise EvalException("Term has not operation nor function")

class Parser:
    
    def unit(value):#unit function, returning itself
        return value
    
    def conjugate(value):
        return value.conjugate()

    def gt(a,b): #wrapper to handle imaginary numbers
        if(a.imag==0 and b.imag==0):
            return float(operator.gt(a.real,b.real))
        else:
            raise TypeError

    def lt(a,b): #wrapper to handle imaginary numbers
        if(a.imag==0 and b.imag==0):
            return float(operator.lt(a.real,b.real))
        else:
            raise TypeError

    #NOTE function names cant start with x since thats an identifier for var
    functions = {'unit':unit,'ceil':math.ceil,'abs':math.fabs,'fac':math.factorial,'floor':math.floor,'exp':cmath.exp,'log':cmath.log,'log1p':math.log1p,'log10':cmath.log10,'sqrt':cmath.sqrt,'acos':cmath.acos,'asin':cmath.asin,'atan':cmath.atan,'cos':cmath.cos,'sin':cmath.sin,'tan':cmath.tan,'degrees':math.degrees,'radians':math.radians,'acosh':cmath.acosh,'asinh':cmath.asinh,'atanh':cmath.atanh,'cosh':cmath.cosh,'sinh':cmath.sinh,'tanh':cmath.tanh}
    
    operators = [{'>':gt,'<':lt},{'+':operator.add,'-':operator.sub},{'%':operator.mod},{'*':operator.mul},{'/':operator.div},{'^':operator.pow}]
    #operations and the different levels starting with the left most beeing zero
    unaryoperators = [{},{},{},{},{},{'+':operator.pos,'-':operator.neg,'*':conjugate}]

    q = None

#   EBNF 

#   plots = term-(-1),[';',term-(-1)],'\n'
#   term-i = [unary-i],term-(i+1),[op-(i+1),term-i] (* -1 is the lowest order term AKA expression *) (* either unary-(i+1) or op-(i+1), unary (since on the left) has higher priority *)
#   term-n = var | num | [function],(,term-(-1),) (* n is the number of the highest order operator *) (* function is optional and if left out it will be unit-function *)

# (* can have additional operators (easy to add) *)
#   op-0 = '>' | '<'
#   op-1 = '+' | '-'
#   op-2 = '*' | '/' | '%'
#   op-3 = '^'
#   unary-3 = '+' | '-' | '*'
#   num = ? all numbers ?
#   var = 'x'
#   function = ? a function listed among the functions, must begin with a lowercase letter and not the letter x ?
    
    def isoperator(self,op,level):
        if(level>=len(self.operators)):
            return False
        return self.operators[level].has_key(op)
    
    def isunary(self,unop,level):
        if(level>=len(self.unaryoperators)):
            return False
        return self.unaryoperators[level].has_key(unop)

    def readfunction(self):#read all letters until you hit an '('
        if(debug):
            print "in readfunction()"
        funcname = ""
        if(self.q.peek()=='('):
            return self.functions["unit"] #special case with unit-function
        while(self.q.peek()!='('):
            if(self.q.peek()=='\n'):
                raise ParseException("missing (")
            funcname +=self.q.get()
        if(not self.functions.has_key(funcname)):
            raise ParseException("'"+funcname+"'"+" is not a function")
        return self.functions[funcname] #general case
    
    def readterm(self,level):
        if(debug):
            print "in readterm(",level,")"
        term = Term()
        if(level==len(self.operators)): #basecase, the highest-order terms spefied by operators
            if(self.q.peek()=='x'):
                self.q.get()
                term.left = Variable()
                return term
            elif(funcbegin.match(self.q.peek())): #if begining of function expression (including the unit function)
                term.func = self.readfunction()
                self.q.get() #read (
                
                term.left = self.readterm(-1)
                if(self.q.get()!=')'):
                    raise ParseException("missing ')'")
                return term
            elif(digit.match(self.q.peek())):
                term.left = Num(self.readnum())
                return term
            else:
                raise ParseException("unable to read term..")
        else:
            #term-i = [unary-i],term-(i+1),[op-(i+1),term-i]
            hasUnary = False
            if(self.isunary(self.q.peek(),level)):
                term.unop = self.readunary(level)
                hasUnary = True
            term.left = self.readterm(level+1)
            if(hasUnary):
                return term
            if(self.isoperator(self.q.peek(),level+1)):
                term.op = self.readoperation(level+1)
                term.right = self.readterm(level)
                return term
            else:
                if(debug):
                    print "skipping level=",level
                return term.left #if nothings special in this termlevel just continue passing, faster when .eval() the expression

    def readoperation(self,level):
        if(debug):
            print "in readoperation(",level,")"
        op = self.q.get()
        if(not self.isoperator(op,level)):#isn't an operator of spec level
            raise ParseException("'"+str(op)+"'"+ " is not a binary operator of level=" + str(level))
        return (self.operators[level])[op]

    def readunary(self,level):
        if(debug):
            print "in readunary()"
        unop = self.q.get()
        if(not self.unaryoperators[level].has_key(unop)): #NOTE not needed always checked in beforehand
            raise ParseException("'"+str(unop)+"' is not a unary operator")

        return (self.unaryoperators[level])[unop]

    def readnum(self):
        if(debug):
            print "in readnum()"
        number = ""
        if(digit.match(self.q.peek())):
            number+=self.q.get()
        else:
            raise ParseException("Not a number")
        while(digit.match(self.q.peek()) or self.q.peek()=='.'):#all the numbers after
            number+=self.q.get()

        try:
            if(self.q.peek()=='i'):#is a complex number
                self.q.get()
                num = float(number)
                return complex(0,num)
            num = float(number)
            return num 
        except ValueError: #ex 3.14.15
            raise ParseException("'"+number+"' is not a float value")

    def readplots(self):
        plots = []
        while(self.q.peek()!='\n'):
            plots.append(self.readterm(-1))
            if(self.q.peek()==';'):#remove the ;
                self.q.get()
        return plots

    def parse(self,str):
        if(debug):
            print "in parse(str)"
        self.q = Queue()
        for token in str:
            if(token!=" "):#remove spaces
                self.q.put(token)
        self.q.put("\n")
        
        try:
            return self.readplots()
        except ParseException as pe:
            print "exception!!1"
            print pe
            print self.q
        return 
            
class Plot:

    function_string = None
    function_trees = None

    xrange = None 

    def pushed_enter(self,event):
        self.plotIt()

    def setTitle(self,title):
        global version_name
        global prgm_name
        self.top.title(prgm_name+" v" + version_name + " [ "+title+" ]")
        return

    def __init__(self,plotdim=(1024,768),axis=(-10.24,10.24,-7.68,7.68),dxstep=1,f=None):
        self.plotdim = plotdim
        self.axis = axis
        self.dxstep = dxstep
        self.dx = float(self.dxstep)/float(axis[1]-axis[0])
        
        self.xrange = frange(self.axis[0],self.axis[1],self.dx)

        self.transformscale = (float(plotdim[0])/float(axis[1]-axis[0]),float(plotdim[1])/float(axis[3]-axis[2]))#xscale = width/(maxx-minx),yscale = height/(maxy-miny)
        self.transformoffset = (axis[0],axis[2])

        self.top = Tk()

        if(f):
            self.setTitle(f)
        else:
            self.setTitle("")

        self.C = Canvas(self.top, bg="black", height=self.plotdim[1], width=self.plotdim[0])
        self.C.pack()

        self.L1 = Label(self.top, text="f(x)=")
        self.L1.pack( side = LEFT)

        self.E1 = Entry(self.top, bd =2,width=90)
        self.E1.pack(side = LEFT)
        self.E1.focus_set()
        self.E1.bind("<Return>",self.pushed_enter)

        self.B = Button(self.top,text="plot",command = self.plotIt)
        self.B.pack(side = LEFT)

        if(f):
            self.E1.insert(0,f)
            self.plotIt()
        else:
            self.plotaxis()

        self.top.mainloop()

        return

    def plotIt(self):
        self.setTitle(self.E1.get())
        
        if(debug):
            print "PLOTS IT!!1"
        p = Parser()
        self.function_trees = p.parse(self.E1.get())
         
        self.clearplot()
        self.plotaxis()
        self.plotfunction()

        return

    def transform(self,p):
        return (self.transformscale[0]*(p[0]-self.transformoffset[0]),self.plotdim[1]-self.transformscale[1]*(p[1]-self.transformoffset[1])) # = scale*(x-minx)

    def clearplot(self):
        self.C.delete(ALL)
        return

    def plotaxis(self):
        self.C.create_line( (self.transform( (self.axis[0],0) )+self.transform( (self.axis[1],0) )),fill="white")
        self.C.create_line( (self.transform( (0,self.axis[2]) )+self.transform( (0,self.axis[3]) )),fill="white")
        
        space = 1.0
        length = 0.15
        #NOTE only correct if centered
        for x in frange(self.axis[0],self.axis[1],space):
            self.C.create_line( (self.transform( (x,length) )+self.transform( (x,-length) )),fill="white")
        
        for y in frange(self.axis[2],self.axis[3],space):
            self.C.create_line( (self.transform( (length,y) )+self.transform( (-length,y) )),fill="white")
        return


    def plotfunction(self):

        for function_tree in self.function_trees:
            f = function_tree.eval
            for x in self.xrange:
                try:
                    p1 =  (x,f(x)) 
                    p2 =  (x+self.dx,f(x+self.dx))
                    
                    if(p1[1].imag==0 and p2[1].imag==0):#if real
                        self.C.create_line( (self.transform((p1[0],p1[1].real))+(self.transform((p2[0],p2[1].real)))) ,fill="green")
                    else:
                        self.C.create_line( (self.transform((p1[0],p1[1].real))+(self.transform((p2[0],p2[1].real)))) ,fill="blue")
                        self.C.create_line( (self.transform((p1[0],p1[1].imag))+(self.transform((p2[0],p2[1].imag)))) ,fill="red")

                except ZeroDivisionError:
                    if(debug):
                        print "ZeroDivision!!1"
                except ValueError:
                    if(debug):
                        print "out ot domain!!1"
                except TypeError:
                    if(debug):
                        print "type error!!1"

        return           

def usage():
    print "Usage:   plot [-d]"
    print "   or:   plot [-d] -p EXPRESSION"
    print "   or:   plot [-d] -c EXPRESSION"
    print "Opens a new plot window, or plots an EXPRESSION, or calculates an EXPRESSION"
    print " "
    print " -c, --calc          calculate the expression"
    print " -d, --debug         debug-mode turned on"
    print " -p, --plot          plot the expression"
    print " -v, --version       get the version number"
    print " "
    print "EXPRESSION with parantheses etc must be inside single quotes."
    print "To plot/calc multiple expressions they should be seperated by semicolons. Ex) 'sin(x);cos(x);x'"
    print " "
    print "Report plot bugs to <jimho@kth.se>"
    print " "
    print "Copyright (c) Jim Holmstrom, 2011"
    return

def version():
    global prgm_name
    global version_name
    print prgm_name + " v" + version_name
    return

def main(argv):
                    
    try:
        opts,args = getopt.getopt(argv,"vhdp:c:",['version','help','debug','plot=','calc='])
    except getopt.GetoptError as e:          
        print str(e)
        usage()                         
        sys.exit(2)                     
    openPlot = True
    for opt, arg in opts:                
        if opt in ("-h", "--help"):
            usage()                     
            sys.exit()
        elif opt in ("-d","--debug"):
            global debug               
            debug = True                  
        elif opt in ("-p", "--plot"): 
            plot = Plot(f=arg)
            openPlot=False
        elif opt in ("-c","--calc"):
            for letter in arg:
                if(letter=='x'):
                    print "must not have x in expression to calculate excplicit value"
                    sys.exit(2)
            p = Parser()
            t = p.parse(arg)
            for tree in t:
                value = tree.eval(0) #a zero just 
                if(value.imag==0.0):
                    print str(value.real) #a fix to take away the (value+0j)
                else: #fix the printout for complex-numbers (could be a method)
                    for letter in str(value):
                        if(letter=='(' or letter==')'):
                            dummy = 1 #dont printout
                        elif(letter=='j'):
                            sys.stdout.write('i')
                        else:
                            sys.stdout.write(letter)
                    sys.stdout.write('\n')

                    
            openPlot=False
        elif opt in ("-v","--version"):
            version()
            sys.exit()

    if(openPlot):
        p = Plot()

    return

#def main():
#    plot = Plot(f="log(x)^2/5")


if(__name__=="__main__"):
    print 'DO NOT USE! it has serious flaws; for example -1+1=-2'
    main(sys.argv[1:])
