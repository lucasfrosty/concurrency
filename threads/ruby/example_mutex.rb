n = 0
mutex = Mutex.new

def increment(value)
	value+1
end


threads = 2.times.map{
	Thread.new {
		1000000.times {
			mutex.synchronize { n = increment(n)}
		}
	}	
}

threads.each { |x| x.join }

puts n