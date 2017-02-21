/* Our boring function returns a channel that lets us communicate with the boring service it provides

We can have more instances of the service */

package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	lucas := boring("Lucas")
	user := boring("User")
	for i := 0; i < 5; i++ {
		fmt.Println(<-lucas)
		fmt.Println(<-user)
	}
	fmt.Println("You're both boring; I'm leaving.")
}

func boring(msg string) <-chan string { // Returns receive-only channel of strings.
	c := make(chan string)
	go func() { // We launch the goroutine from inside the function.
		for i := 0; ; i++ {
			c <- fmt.Sprintf("%s: %d", msg, i)
			time.Sleep(time.Duration(rand.Intn(1e3)) * time.Millisecond)
		}
	}()
	return c // Return the channel to the caller.
}