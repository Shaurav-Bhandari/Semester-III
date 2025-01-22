from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.keys import Keys
import time

USERNAME = ""
PASSWORD = ""

CHROMEDRIVER_PATH = r"C:\\chromedriver.exe"

service = Service(executable_path=CHROMEDRIVER_PATH)
options = webdriver.ChromeOptions()
driver = webdriver.Chrome(service=service, options=options)

def login_and_get_cookies():
    login_url = "https://www.instagram.com/"
    driver.get(login_url)

    username_input = driver.find_element("name", "username")
    username_input.send_keys(USERNAME)
    username_input.send_keys(Keys.RETURN)
    time.sleep(7)

    password_input = driver.find_element("name", "password")
    password_input.send_keys(PASSWORD)
    password_input.send_keys(Keys.RETURN)
    time.sleep(7)

    cookies = driver.get_cookies()

    for cookie in cookies:
        print(f"Name: {cookie['name']}, Value: {cookie['value']}")

    driver.quit()

if name == "main":
    login_and_get_cookies()