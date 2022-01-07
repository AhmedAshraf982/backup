import selenium
from selenium import webdriver
from selenium.common.exceptions import NoSuchElementException  #to check if element exists
from time import sleep
import math
import random
import datetime
import csv

class Record():
    def __init__(self):
        self.name = ""
        self.father = ""
        self.age = 0
        self.gender = ''
        self.address = ""
        self.dob = ""
        self.issue_date = ""
        self.expiry_date = ""

    def printdata(self):
        print(self.name, self.father, self.age, self.gender, self.address, self.dob, self.issue_date, self.expiry_date)

driver = webdriver.Chrome(r'C:/Users/Hp/Desktop/chromedriver_win32 _96/chromedriver.exe')

driver.get("https://kidadl.com/articles/best-pakistani-names-for-girls-and-boys")
sleep(5)

def check_exists(css):
    try:
        driver.find_element_by_css_selector(css)
    except NoSuchElementException:
        return False
    return True

names = []

for x in range(200):
    if check_exists("#__next > div > div > div.Box-sup55n-0.gQPbTc > div > div > div > div > div.Flex-sc-11xujgn-0.bXFXc.container-article-text > div.Box-sup55n-0.ArticleBody__BaseArticleBody-yq0zjv-0.ArticleBody__ArticlesBody-yq0zjv-1.gzqKZH.jxtqVj.edNru.rich-text-article-body.in-content-ads > p:nth-child(" + str(x+11) + ") > strong"):
        text = driver.find_element_by_css_selector("#__next > div > div > div.Box-sup55n-0.gQPbTc > div > div > div > div > div.Flex-sc-11xujgn-0.bXFXc.container-article-text > div.Box-sup55n-0.ArticleBody__BaseArticleBody-yq0zjv-0.ArticleBody__ArticlesBody-yq0zjv-1.gzqKZH.jxtqVj.edNru.rich-text-article-body.in-content-ads > p:nth-child(" + str(x+11) + ") > strong").text
        names.append(str(text))

driver.close()
area = [
"Baldia",
"Bin Qasim",
"Gadap",
"Gulberg",
"Gulshan",
"Jamshed",
"Kemari",
"Korangi",
"Landhi",
"Liaquatabad",
"Lyari",
"Malir",
"New Karachi",
"North Nazimabad",
"Orangi",
"Saddar",
"Shah Faisal",
"SITE",
"Gulshan e Iqbal",
"Gulistan e Jouhar",
"Sadi Town",
"Gulzar e Hijri"]

num = 1000000




for x in range(num):
    record = Record()
    record.name = names[round(random.random()*100) % len(names)] + " " + names[round(random.random()*100) % len(names)]
    record.father = names[round(random.random()*100) % len(names)] + " " + names[round(random.random()*100) % len(names)]
    record.age = (round(random.random()*100))
    start_date = datetime.date(2021, 1, 1)
    end_date = datetime.date(2021, 12, 1)
    time_between_dates = end_date - start_date
    days_between_dates = time_between_dates.days
    random_number_of_days = random.randrange(days_between_dates)
    random_date = start_date + datetime.timedelta(days=random_number_of_days)
    record.dob = random_date
    start_date = datetime.date(2021, 1, 1)
    end_date = datetime.date(2021, 2, 1)
    time_between_dates = end_date - start_date
    days_between_dates = time_between_dates.days
    random_number_of_days = random.randrange(days_between_dates)
    random_date = start_date + datetime.timedelta(days=random_number_of_days)
    record.issue_date = random_date
    start_date = datetime.date(2021, 1, 1)
    end_date = datetime.date(2021, 12, 5)
    time_between_dates = end_date - start_date
    days_between_dates = time_between_dates.days
    random_number_of_days = random.randrange(days_between_dates)
    random_date = start_date + datetime.timedelta(days=random_number_of_days)
    record.expiry_date = random_date
    record.address = area[round(random.random()*100) % len(area)]
    record.gender = 'M' if random.random()*10 > 5 else 'F'
    nadra = []
    nadra.append(record.name)
    nadra.append(record.father)
    nadra.append(record.age)
    nadra.append(record.gender)
    nadra.append(record.address)
    nadra.append(record.dob)
    nadra.append(record.issue_date)
    nadra.append(record.expiry_date)
    with open('nadra.csv', 'a', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(nadra)


