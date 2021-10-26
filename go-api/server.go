package main
import (
    "encoding/json"
    "log"
    "net/http"
    "fmt"
    "io/ioutil"
    "database/sql"
    _ "github.com/go-sql-driver/mysql"
    // "net/smtp"
    mail "github.com/xhit/go-simple-mail/v2"
)

type Contact struct {
    Name string `json:"name"`
    Email string `json:"email"`
    Phone string `json:"phone"`
    Description string `json:"desc"`
}


func main() {
    http.HandleFunc("/contact", test)
    http.HandleFunc("/", home)
    fmt.Println("Starting server on the port 8080...")
    log.Fatal(http.ListenAndServe(":4000", nil))
}


func test(w http.ResponseWriter, r *http.Request) {
    body, err := ioutil.ReadAll(r.Body)
    rawIn := json.RawMessage(string(body))
    bytes, err := rawIn.MarshalJSON()
    if err != nil {
        panic(err)
    }
    var p Contact
    err = json.Unmarshal(bytes, &p)
    if err != nil {
        panic(err)
    }
    //  mysql connection
    db, err := sql.Open("mysql", "root:9026040@tcp(127.0.0.1:3306)/Test")
    db.SetMaxIdleConns(0)
    if err != nil {
        panic(err.Error())
    }
    defer db.Close()
    insert, err := db.Query("INSERT INTO Contact(name, phone, email, descrption) VALUES ('" + p.Name + "','" + p.Phone +"','"+ p.Email + "','" + p.Description + "')")
    if err != nil {
        panic(err.Error()) // proper error handling instead of panic in your app
    }else{
        fmt.Println("Record added in db: ", p)
    }
    defer insert.Close()
    // results, err := db.Query("SELECT * FROM Contact")
    // for results.Next() {
    //     var record Contact
    //     // for each row, scan the result into our tag composite object
    //     err = results.Scan(&record.Name, &record.Phone, &record.Email, &record.Description)
    //     if err != nil {
    //         panic(err.Error()) // proper error handling instead of panic in your app
    //     }
    //             // and then print out the tag's Name attribute
    //     fmt.Println(record)

    // }
    // from := "mailerhere10@gmail.com"
	// password := "90260405575"
	// to := []string{"ahmednaeem.career@gmail.com"}
	// smtpHost := "smtp.gmail.com"
	// smtpPort := "587"
    // // string_msg := "Contact request Received: Name: " + p.Name + ", Phone: "+ p.Phone + ", Email: " + p.Email + ", Description: " + p.Description
	// message := []byte("Contact request Received: Name: Ahmed, Phone: 01234567890, Email: abc@gmail.com, Description: hello egcitech!")

	// // Create authentication
	// auth := smtp.PlainAuth("", from, password, smtpHost)

	// // Send actual message
	// err_ := smtp.SendMail(smtpHost+":"+smtpPort, auth, from, to, message)
	// if err_ != nil {
	// 	log.Fatal(err_)
	// }
    var htmlBody = `
<html>
<head>
   <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
</head>
<body>
   <h3>A user has sent some information:</h3>
   <p>Name: ` + p.Name + `</p>
   <p>Email: ` + p.Email + `</p>
   <p>Phone: ` + p.Phone + `</p>
   <p>Description: ` + p.Description + `</p>
</body>
`
    server := mail.NewSMTPClient()
	server.Host = "smtp.gmail.com"
	server.Port = 587
	server.Username = "mailerhere10@gmail.com"
	server.Password = "90260405575"
	server.Encryption = mail.EncryptionTLS

	smtpClient, err := server.Connect()
	if err != nil {
		log.Fatal(err)
	}

	// Create email
	email := mail.NewMSG()
	email.SetFrom("mailerhere10@gmail.com")
	email.AddTo("ahmednaeem.career@gmail.com")
	email.SetSubject("Contact Request Received!")

	email.SetBody(mail.TextHTML, htmlBody)
	// Send email
	err = email.Send(smtpClient)
	if err != nil {
		log.Fatal(err)
	}
}

func home(rw http.ResponseWriter, req *http.Request){
    fmt.Fprintf(rw, "Hello!")
}