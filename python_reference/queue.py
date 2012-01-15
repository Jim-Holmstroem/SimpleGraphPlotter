class Node:
    value = None
    next  = None
    
    def put(self,x):
        self.next = x
        return
    
    def get(self):
        return self.value
        
    def isempty(self):
        return (self.value==None)
        
    def __str__(self):
        return str(self.value)
    
class Queue:
    first = None
    last = None
    length = 0
    
    def put(self,x):
        self.length+=1
        
        p = Node()
        p.value = x
        
        if self.first==None:
            self.first = p
            self.last = p
        else:
            self.last.next = p
            self.last = p
        return
    
    def peek(self):
        return self.first.value

    def get(self):
        self.length-=1
        if(self.isempty()):
            raise Exception
        getthis = self.first.value # get the value to return first
        self.first = self.first.next #set the next node as first
        return getthis
        
    def isempty(self):
        return (self.first==None)
        
    def putQueue(self,q):
        while(not q.isempty()):
            self.put(q.get())
        
        return
    	

    def __eq__(self, m):
	return self.retVector() == m.retVector()

    def __neq__(self, m):
	return self.retVector() != m.retVector()


    def getVector(self): #gets all elements but destructive since it empties the queue
        vector = []
        while(not self.isempty()):
            vector += [self.get()]
        return vector
        
    def retVector(self): 
        vector = self.getVector()
        self.putVector(vector) #since all nodes are taken away we have to put them back before returning
        return vector
    
    def putVector(self,vector):
        for i in range(len(vector)):
            self.put(vector[i])   
        
    def __init__(self,vector = []):
        for i in range(len(vector)):
            self.put(vector[i])
        return
    
    def __len__(self):
        return self.length
    


    def __str__(self):
        str_values = ""
        values = self.retVector()
        for i in range(len(values)):
            str_values += "%s | "%values[i]
        
        return "Queue=| %s"%str_values

    def flush(self):
        while(not self.isempty()):
            self.get()

    def splitat(self,i):
    
        vector = self.retVector()
        
        if(len(vector)<i):
            raise ValueError
            
        self.flush() # empty the self-queue since
            
        return Queue(vector[0:i]),Queue(vector[i:len(vector)])
    
    def splitInHalf(self): #only for even length arrays
        
        if(len(self)%2==1):
            raise ValueError

        return self.splitat(len(self)/2)
        
        
        


