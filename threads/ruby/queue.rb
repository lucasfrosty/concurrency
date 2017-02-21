require 'thread'
queue = Queue.new

producer = Thread.new do
  10.times do |i|
     # sleep rand(i) # simulate expense
     queue << i
     puts "produced #{i}"
  end
end

consumer = Thread.new do
  10.times do |i|
     value = queue.pop
     # sleep rand(i/2) # simulate expense
     puts "consumed #{value}"
  end
end

	
consumer.join