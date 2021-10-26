package main

import (
	"log"
	"net/smtp"
)

func main() {
	// Configuration
	from := "mailerhere10@gmail.com"
	password := "90260405575"
	to := []string{"ahmednaeem.career@gmail.com"}
	smtpHost := "smtp.gmail.com"
	smtpPort := "587"

	message := []byte("This email is a sample to test go.")

	// Create authentication
	auth := smtp.PlainAuth("", from, password, smtpHost)

	// Send actual message
	err := smtp.SendMail(smtpHost+":"+smtpPort, auth, from, to, message)
	if err != nil {
		log.Fatal(err)
	}
}