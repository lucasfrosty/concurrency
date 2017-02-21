mutex = Mutex.new
resource = ConditionVariable.new
 
a = Thread.new {
	mutex.synchronize {
		puts "Hello"
		resource.wait(mutex)
		puts "world"
	}
}


b = Thread.new {
	mutex.synchronize {
		puts "hello!"
		# sleep 1
		resource.signal
	}
}

a.join
b.join