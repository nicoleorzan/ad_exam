'''
Exam requests: 

1. Write a class PostcardList that satisfies the tests (defined using unittest). 
2. OPTIONAL) Populate and save one (or more) file(s) to test other groups implementations using unittest.

SPECIFICATIONS: 
Class PostcardList reads/writes Postcard messages from/to a properly formatted file: each record (i.e., file's line) is a Postcard. 
The Postcard format is "date:$(DATE); from:$(SENDER); to:$(RECEIVER);" (e.g., "date:2009-12-24; from:Daisy; to:Donald;"). For the sake of simplicity, the message is not considered.

Class PostcardList must have at least these attributes:
 - _file: file name, eventually with the full path.
 - _postcards: list of postcards read from _file.
 - _date: is a dict where the key is the string date, and the value is a list of indices. Each index refers to the corresponding record.
 - _from: is a dict where the key is the string sender, and the value is a list of indices. Each index refers to the corresponding record.
 - _to:   is a dict where the key is the string receiver, and the value is a list of indices. Each index refers to the corresponding record.

Class PostcardList must manage the I/O file through the following member functions. Note that you are free to choose the appropriate arguments, but the function names must be as follows:  
 - writeFile(self,...): write self.{_date,_from,_to} to self._file  
 - readFile(self,...): from self._file read self.{_date,_from,_to}    
 - parsePostcards(self,...): parse self._postcards, set self.{_date,_from,_to} 
 - updateFile(self,...): as write but appending to self._file 
 - updateLists(self,...): as read but appending to self._postcards 
 - getNumberOfPostcards(self): returns length of self._postcards

Class PostcardList must manage the sorting of dates/senders/receivers. Note that the names and arguments of the functions are fixed as follows: 
 - getPostcardsByDateRange(self,date_range): returns the postcards within a date_range
 - getPostcardsBySender(self, sender): returns the postcards from a sender
 - getPostcardsByReceiver(self, receiver): returns the postcards to a receiver
'''

import unittest
import datetime  # use this module to deal with dates:  https://docs.python.org/3/library/datetime.html

class PostcardList(object): 

	populatePostcards = []
	
	_postcards = []
	_file = ''
	_date = {}
	_from = {}
	_to = {}

	def writeFile(self,filename):
		pass
	
	
	def readFile(self,_file):
		self._postcards = []
		self._date = {}
		self._from = {}
		self._to = {}
		with open(_file) as datafile:
			for line in datafile:
				self._postcards.append(str(line))
			#print("readfile calling len", self.getNumberOfPostcards(self._postcards))
		self.parsePostcards()
		return self._date, self._from, self._to

	def parsePostcards(self):
		for i,elem in enumerate(self._postcards):
			elem = elem.replace(" ","").split(";",3)
			key1 = datetime.datetime.strptime(elem[0].split(":")[1],"%Y-%m-%d")
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
		return self._date, self._from, self._to 
		
		return self._date,self._from, self._to
			
	def updateFile(self,filename):
		pass
	
	def updateLists(self, filename):
		pass
	
	def getNumberOfPostcards(self,_postcards):
		num = len(self._postcards)
		pass
		
	def getPostcardsByDateRange(self,date_range):
		pass
		
	def getPostcardsBySender(self, sender):
		lista = []	
		#print("sender=",sender)
		#print("lenght of _postcards",self.getNumberOfPostcards(self._postcards))
		for key, value in self._from.items():  
			if (sender==key):
				#print("value len",len(value))
				#print("value tot",value)
				for i,val in enumerate(value):
					#print("val=",val)
					#print("i=",i)
					#print(self._postcards[val])
					lista.append(self._postcards[val])
		return lista
	
	def getPostcardsByReceiver(self, receiver): 
		lista = []
		for key, value in self._to.items():  
			if (receiver==key):
				for i,val in enumerate(value):
					lista.append(self._postcards[val])
		return lista
		
    ########################
    # define attributes here
    #pass
    ########################


########################
# TO COMMENT 
#from exam_solution import PostcardList # overrides the class define above
########################


class Test(unittest.TestCase):

    @classmethod
    def setUpClass(self):
        self._files = ['./exam_postcard_list{}.txt'.format(i) \
                           for i in range(10)]
        self._PstLst = [PostcardList() for f in self._files]
        
        
        [p.readFile(f) for f,p in zip(self._files,self._PstLst)]
    def test_missing_attributes(self): 
        attributes_to_define = ['populatePostcards',\
                                '_file','_postcards','_from','_to',\
                                'writeFile','readFile','parsePostcards',\
                                'updateFile','updateLists',\
                                'getNumberOfPostcards',\
                                'getPostcardsByDateRange',\
                                'getPostcardsBySender',\
                                'getPostcardsByReceiver']
        for attr in attributes_to_define:
            if attr not in dir(self._PstLst[0]): 
                raise Exception(attr+' is missing')

    def test_check_getPostcardByDateRange(self): 
        dr_test = []
        for i in [0,1,4,6]: 
            dr_test.append(\
                self._PstLst[i].getPostcardsByDateRange(date_range=\
                   (datetime.datetime.strptime('2008-1-1', "%Y-%m-%d"),\
                    datetime.datetime.strptime('2010-12-31', "%Y-%m-%d"))))
        self.assertListEqual(sorted(dr_test[0]),sorted(['date:2010-06-23; from:Sneezy; to:Alice;\n', 'date:2009-12-12; from:Dopey; to:Peter;\n', 'date:2008-03-23; from:Sneezy; to:Pluto;\n', 'date:2008-06-03; from:Goofy; to:Pluto;\n'])) 
        self.assertEqual(len(dr_test[1]),1)
        self.assertListEqual(sorted(dr_test[2]),sorted(['date:2010-03-30; from:Louie; to:Sneezy;\n', 'date:2010-03-05; from:Goofy; to:Dopey;\n', 'date:2009-11-08; from:Daisy; to:Minnie;\n', 'date:2010-07-13; from:Bashful; to:Louie;\n', 'date:2008-06-29; from:Huey; to:Dopey;\n', 'date:2009-01-04; from:Alice; to:Hook;\n', 'date:2009-04-28; from:Bashful; to:Mickey;\n']))
        self.assertEqual(len(dr_test[3]),7)

    def test_check_getPostcardBySender(self): 
        s_test = []
        for i in [2,3,5,7]:
            for sender in ['Daisy','Bashful','Peter']:
                s_test.append(\
                    self._PstLst[i].getPostcardsBySender(sender=sender))
        self.assertIn('date:2011-12-11; from:Daisy; to:Goofy;\n',s_test[0])
        self.assertListEqual(s_test[1],[])
        self.assertEqual(len(s_test[2]),1)
        self.assertEqual(len(s_test[5]),0)
        self.assertGreater(len(s_test[8]),len(s_test[9]))

    def test_check_getPostcardByReceiver(self): 
        r_test = []
        for i in [0,3,8,9]:
            for receiver in ['Peter','Hook','Alice','SnowWhite']:
            	r_test.append(\
                  self._PstLst[i].getPostcardsByReceiver(receiver=receiver))
        self.assertIn('date:2009-12-12; from:Dopey; to:Peter;\n',r_test[0])
        self.assertListEqual(r_test[1],['date:2016-10-23; from:Sneezy; to:Hook;\n'])
        self.assertEqual(len(r_test[2]),2)
        self.assertEqual(len(r_test[6]),3)

    def test_check_sent_received_when(self): 
        srw_test = []
        for ii in range(10):
            for jj in ["Mickey","Minnie","Goofy","Pluto","Donald","Daisy","$crooge","Huey","Dewey","Louie","Peter","Hook","Alice","SnowWhite","Doc","Sleepy","Sneezy","Bashful","Dopey","Happy","Grumpy"]:
                try:
                    srw_test.append(self._PstLst[ii]._from[jj])
                    srw_test.append(self._PstLst[ii]._to[jj])
                    srw_test.append(self._PstLst[ii]._date[jj])
                except: pass
        self.assertListEqual(srw_test[0],[1])
        self.assertListEqual(srw_test[130],[14,25])
        self.assertListEqual(srw_test[138],[10])
        self.assertListEqual(srw_test[140],[15])
        self.assertListEqual(srw_test[192],[13,26])
        self.assertListEqual(srw_test[203],[6, 9, 11, 12, 24, 31, 42])

if __name__ == '__main__':

    unittest.main()
