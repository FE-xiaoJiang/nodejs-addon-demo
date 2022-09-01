function MyObject(value) {
  this.value_ = value || 0
 }

 MyObject.prototype.plusOne = function() {
  return ++this.value_
 }
 
 exports.MyObject = MyObject
 