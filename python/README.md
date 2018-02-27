# Python exam

The file Postcard.py contains the implementation of the class PostcardList. To
use it in another program it must be imported, for example with the statement
_from Postcard import PostcardList_

Thanks to the function _readFile(filename)_ the class is able to read all the strings representing a postcard from the file "_filename_" and save it in his _\_postcards_ vector.
This vector is then parsed by the function _parsePostcards()_ that, from this, fills the 3 dictionaries _\_date_, _\_from_ and to _\_to_, with, for example, the date as key and a vector containing the index of those postcards corresponding to that date in the vector _\_postcards_. For the dates we used the datetime module, that easily allow the user to manage and compare them.
The _postcards vector can be expanded with the content of another file using the function _updateList(filename)_ that simply append to it the strings read from "_filename_". This function then calls again _parsePostcards_ to generate the dictionaries.
The class contains also other methods to manipulate files: _writeFile(filename)_ writes all the content of _\_postcards_ to the passed file, instead the method _updateFile(filename)_ appends to the file the content of _\_postcards_.
Once the postcards are read from the file, in the class there are also some functions that allow the user to search for some information insede the saved postcards:
 - _getPostcardsBySender(sender)_ returns a vector with all the postcards corresponding to the specified sender
 - _getPostcardsByReceiver(receiver)_ returns a vector with all the postcards with the specified receiver
 - _getPostcardsByDateRange(date_range)_ return a vector with all the postcards whose date falls inside the range specified by the vector date_range = (date_min, date_max)

Finally, we add to the class some functions that print all the data stored inside it, i.e. _print\_file()_, prints the name of the file currently stored in the class, _print\_postcards()_ prints the whole vector _\_postcards_, and _print\_to()_, _print\_from()_,  _print\_date()_ print the contents of the relative dictionaries.