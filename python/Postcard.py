import datetime  # use this module to deal with dates:  https://docs.python.org/3/library/datetime.html


class PostcardList(object): 

	populatePostcards = []
	
	_postcards = []
	_file = ''
	_date = {}
	_from = {}
	_to = {}
        
	def writeFile(self,filename):
		with open(filename, "w") as datafile:
			for line in self._postcards:
				datafile.write(line)
				datafile.write("\n")
	
	
	def readFile(self,filename):
		self._file = filename
		self._postcards = []
		with open(self._file, "r") as datafile:
			for line in datafile:
				self._postcards.append(str(line))  
		
		self.parsePostcards()
		

	def parsePostcards(self):
		self._date = {}
		self._from = {}
		self._to = {}
		for i,elem in enumerate(self._postcards):
			elem = elem.replace(" ","").split(";",3)
			key1 = datetime.datetime.strptime(elem[0].split(":")[1],"%Y-%m-%d")
			key1 = key1.date()  # convert datetime to date 
			key2 = elem[1].split(":")[1]
			key3 = elem[2].split(":")[1]
			if key1 not in self._date:
				self._date[key1] = [i]
			else:
				self._date[key1].append(i)
			if key2 not in self._from:
				self._from[key2] = [i]
			else:
				self._from[key2].append(i)
			if key3 not in self._to:
				self._to[key3] = [i]
			else:
				self._to[key3].append(i)
			
	def updateFile(self,filename):
		with open(filename, "a") as datafile:
			for line in self._postcards:
				datafile.write(line)
				datafile.write("\n")
	
	def updateLists(self, filename):
		self._file = filename
		with open(self._file, "r") as datafile:
			for line in datafile:
				self._postcards.append(str(line))
		self.parsePostcards()
	
	
	def getNumberOfPostcards(self,_postcards):
		return len(self._postcards)
		
		
	def getPostcardsByDateRange(self,date_range):
		lista = []
		
		inf = date_range[0].date()
		sup = date_range[1].date()
		
		
		for date in self._date:
			if( date >= inf and date <= sup ):
				for i in self._date[date]:
					lista.append(self._postcards[i])
		return lista
		
		
		
		
	def getPostcardsBySender(self, sender):
		lista = []
		for key, value in self._from.items():  
			if (sender==key):
				for i,val in enumerate(value):
					lista.append(self._postcards[val])
		return lista
		
		
	
	def getPostcardsByReceiver(self, receiver): 
		lista = []
		for key, value in self._to.items():  
			if (receiver==key):
				for i,val in enumerate(value):
					lista.append(self._postcards[val])
		return lista




	def print_file(self):
		print("_file = {}".format(self._file))

	def print_postcards(self):
		print("POSTCARDS:")
		for i in self._postcards:
			print(i)
			
	def print_date(self):
		print("DATE:")
		for i in self._date:
			print("date: {} index: {}".format(i, self._date[i]) )
			
	def print_from(self):
		print("FROM:")
		for i in self._from:
			print("from: {} index: {}".format(i, self._from[i]) )
			
	def print_to(self):
		print("TO:")
		for i in self._to:
			print("to: {} index: {}".format(i, self._to[i]) )

	def print_all(self):
		self.print_file()
		self.print_postcards()
		self.print_date()
		self.print_from()
		self.print_to()


