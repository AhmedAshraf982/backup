import threading
from tkinter import *
import tkinter
import selenium
import uuid
import os
import time
from selenium import webdriver
from tkinter import filedialog
import requests
from selenium import webdriver
from tkinter import filedialog
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains
from selenium.common.exceptions import ElementClickInterceptedException, NoSuchElementException, ElementNotInteractableException, StaleElementReferenceException
from datetime import datetime
import time
import sys
import random     
import traceback
import pyautogui
import os

pyautogui.FAILSAFE = False

main_profile_list=[]
main_cart_list=[]
main_ws_list=[]
main_surf_list=[]
main_keyword_list=[]
main_specific_list=[]
stopper=[]
window=tkinter.Tk()
def check_exists_by_xpath(driver,xpath):
    '''
    Function to check the presence of an element
    '''
    try:
        driver.find_element_by_xpath(xpath)
    except NoSuchElementException:
        return False
    return True

def add_to_shoppping_list(driver, randomWaitTime, i):
    try:
        wish_list_btn = driver.find_element_by_xpath('//*[@id="add-to-wishlist-button-submit"]')
        pyautogui.moveTo(driver.find_element_by_xpath(wish_list_btn).location['x'], driver.find_element_by_xpath(wish_list_btn).location['y'], 1)
        wish_list_btn.click()
        time.sleep(randomWaitTime)
        if check_exists_by_xpath(driver, '//span[@class="a-size-base atwl-list-name-expand a-nowrap"]'):
            add_to_shoppping_list = driver.find_element_by_xpath('//span[@class="a-size-base atwl-list-name-expand a-nowrap"]').click()
            pyautogui.moveTo(driver.find_element_by_xpath('//span[@class="a-size-base atwl-list-name-expand a-nowrap"]').location['x'], driver.find_element_by_xpath('//span[@class="a-size-base atwl-list-name-expand a-nowrap"]').location['y'], 1)
        elif check_exists_by_xpath(driver, '//*[@id="WLHUC_continue"]/span/span'):
            add_to_shoppping_list = driver.find_element_by_xpath('//*[@id="WLHUC_continue"]/span/span').click()
            pyautogui.moveTo(driver.find_element_by_xpath('//*[@id="WLHUC_continue"]/span/span').location['x'], driver.find_element_by_xpath('//*[@id="WLHUC_continue"]/span/span').location['y'], 1)
    except:
        if check_exists_by_xpath(driver, f'//div[@data-index="{i}"]'):
            driver.forward()
        wish_list_btn = driver.find_element_by_xpath('//*[@id="add-to-wishlist-button-submit"]')
        ActionChains(driver).move_to_element(wish_list_btn).click()
        time.sleep(randomWaitTime)
        if check_exists_by_xpath(driver, '//span[@class="a-size-base atwl-list-name-expand a-nowrap"]'):
            add_to_shoppping_list = driver.find_element_by_xpath('//span[@class="a-size-base atwl-list-name-expand a-nowrap"]').click()
        elif check_exists_by_xpath(driver, '//*[@id="WLHUC_continue"]/span/span'):
            add_to_shoppping_list = driver.find_element_by_xpath('//*[@id="WLHUC_continue"]/span/span').click()


def scroll_to_reviews(driver):
    if check_exists_by_xpath(driver, '//*[@id="reviewsMedley"]'):
        reviews_part = driver.find_element_by_xpath('//*[@id="reviewsMedley"]')
        ActionChains(driver).move_to_element(reviews_part).perform()
    elif check_exists_by_xpath(driver, '//*[@id="cm-cr-dp-aw-review-header"]'):
        reviews_part = driver.find_element_by_xpath('//*[@id="cm-cr-dp-aw-review-header"]')
        ActionChains(driver).move_to_element(reviews_part).perform()
    pyautogui.moveTo(reviews_part.location['x'], reviews_part.location['y'], 1)
    time.sleep(random.randint(4, 8))

def mark_helpful(driver, randomWaitTime):
    if check_exists_by_xpath(driver, '//i[@class="a-icon a-icon-star-small a-star-small-5 review-rating aok-align-center"]'):
        ActionChains(driver).move_to_element(driver.find_element_by_xpath('//i[@class="a-icon a-icon-star-small a-star-small-5 review-rating aok-align-center"]')).perform()
        time.sleep(randomWaitTime)
        mark_as_helpful = driver.find_element_by_xpath('//div[@class="a-section celwidget"]//input[@data-hook="vote-helpful-button"]').click()
        pyautogui.moveTo(driver.find_element_by_xpath('//div[@class="a-section celwidget"]//input[@data-hook="vote-helpful-button"]').location['x'], driver.find_element_by_xpath('//div[@class="a-section celwidget"]//input[@data-hook="vote-helpful-button"]').location['y'], 1)
    time.sleep(randomWaitTime)
    main_page = driver.find_element_by_xpath('/html')
    main_page.send_keys(Keys.HOME)
    time.sleep(randomWaitTime)

def click_on_image(driver):
    if check_exists_by_xpath(driver, '//*[@id="main-image-container"]'):
        image_big = driver.find_element_by_xpath('//*[@id="main-image-container"]').click()
        pyautogui.moveTo(driver.find_element_by_xpath('//*[@id="main-image-container"]').location['x'], driver.find_element_by_xpath('//*[@id="main-image-container"]').location['y'], 1)
    elif check_exists_by_xpath(driver, '//*[@id="image-block"]'):
        image_big = driver.find_element_by_xpath('//*[@id="image-block"]').click()
        pyautogui.moveTo(driver.find_element_by_xpath('//*[@id="image-block"]').location['x'], driver.find_element_by_xpath('//*[@id="image-block"]').location['y'], 1)
    shuffling = list(range(1, 9))
    random.shuffle(shuffling)
    for image_count in shuffling:
        try:
            time.sleep(random.randint(1,2))
            ActionChains(driver).move_to_element(driver.find_element_by_xpath(f'//*[@id="anonCarousel4"]/ol/li[{image_count}]//img')).click().perform()
            pyautogui.moveTo(driver.find_element_by_xpath(f'//*[@id="anonCarousel4"]/ol/li[{image_count}]//img').location['x'], driver.find_element_by_xpath(f'//*[@id="anonCarousel4"]/ol/li[{image_count}]//img').location['y'], 1)
            time.sleep(random.randint(4, 8))
        except:
            break
def do_randomly(functions_list):
    random_index = random.randint(0, 1)
    if random_index == 0:
        popped = functions_list.pop(random_index)   

    elif random_index==1:
        popped = functions_list.pop(random_index)
    return [functions_list[0], popped]
def main_bot(profiles, keywords,profile_id):
    '''
    This class contains all the functionalities of the bot to visit Amazon
    '''
    mla_profile_id = profiles.split()
    try:
            date = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            max_wait_time = 7
            randomWaitTime = random.randint(3, max_wait_time)
            # mla_profile_id = ['9527B281-92A2-47BD-83C1-DA2682051A84', 'D203BDF3-278F-432F-9E69-A01427439776']

            # for profile in mla_profile_id:
            mla_url = 'http://127.0.0.1:35000/api/v1/profile/start?automation=true&profileId='+mla_profile_id[profile_id]
            resp = requests.get(mla_url)
            json = resp.json()
            print(json)
            chrome_options = Options()
            chrome_options.add_experimental_option("debuggerAddress", json['value'][7:])
            chrome_driver = r'chromedriver.exe'
            driver = webdriver.Chrome(chrome_driver, options=chrome_options)
            driver.maximize_window()
            driver.minimize_window()
            driver.maximize_window()
            driver.get('https://www.amazon.com/')
            action = ActionChains(driver)
            randomKeywords = random.randint(0, len(keywords))
            # Searching
            if check_exists_by_xpath(driver, '//*[@id="nav-search-keywords"]'):
                search_box = driver.find_element_by_xpath('//*[@id="nav-search-keywords"]')
            elif check_exists_by_xpath(driver, '//*[@id="twotabsearchtextbox"]'):
                search_box = driver.find_element_by_xpath('//*[@id="twotabsearchtextbox"]')
            pyautogui.moveTo(search_box.location['x'], search_box.location['y'], 1)
            search_box.send_keys(f'{keywords[randomKeywords]}')
            search_box.send_keys(Keys.RETURN)
            driver.refresh()

            # Clicking on card links
            item = 4
            upper_limit = random.randint(7, 9)
            print(f'I will now visit {upper_limit-(item)} product pages')
            for i in range(4, upper_limit):
                try:
                    if not check_exists_by_xpath(driver, f'//div[@data-index="{i}"]//a'):
                        continue
                    else:
                        time.sleep(randomWaitTime*1.5)
                        if check_exists_by_xpath(driver, f'//div[@data-index="{i}"]//a[@class="a-link-normal a-text-normal"]'):
                            cards = driver.find_element_by_xpath(f'//div[@data-index="{i}"]//a[@class="a-link-normal a-text-normal"]').click()
                        elif check_exists_by_xpath(driver, f'//div[@data-index="{i}"]//a[@title="product-detail"]'):
                            cards = driver.find_element_by_xpath(f'//div[@data-index="{i}"]//a[@title="product-detail"]').click()
                        time.sleep(randomWaitTime)
                        # Hover over image
                        click_on_image(driver)
                        time.sleep(randomWaitTime)
                        if not check_exists_by_xpath(driver, '//*[@id="main-image-container"]'):
                            driver.back()
                        if driver.current_url == 'https://www.amazon.com/':
                            driver.forward()
                        time.sleep(randomWaitTime)
                        if check_exists_by_xpath(driver, f'//div[@data-index="{i}"]//a[@class="a-link-normal a-text-normal"]'):
                            driver.forward()
                        # Scrolling to the review part
                        try:
                            scroll_to_reviews(driver)
                        except NoSuchElementException:
                            upper_limit += 1
                            print('The product page has no reviews, moving on')
                            continue
                        # Marking a five star review as helpful and Scrolling to the starting
                        mark_helpful(driver, randomWaitTime)
                        time.sleep(randomWaitTime)
                        if check_exists_by_xpath(driver, '//*[@id="productDetails_secondary_view_div"]/h3/span[1]'):
                            try:
                                ActionChains(driver).move_to_element(driver.find_element_by_xpath('//*[@id="productDetails_secondary_view_div"]/h3/span[1]')).perform()
                                pyautogui.moveTo(driver.find_element_by_xpath('//*[@id="productDetails_secondary_view_div"]/h3/span[1]').location['x'], driver.find_element_by_xpath('//*[@id="productDetails_secondary_view_div"]/h3/span[1]').location['y'], 1)
                            except ElementNotInteractableException:
                                print('Unable to scroll to the Product Info Page')
                                driver.refresh()
                            time.sleep(randomWaitTime)
                        try:
                            if check_exists_by_xpath(driver, '//*[@id="sellerProfileTriggerId"]'):
                                driver.find_element_by_xpath('/html').send_keys(Keys.HOME)
                                try:
                                    driver.find_element_by_xpath('//*[@id="sellerProfileTriggerId"]').click()
                                except ElementNotInteractableException:
                                    driver.get(driver.find_element_by_xpath('//*[@id="sellerProfileTriggerId"]').get_attribute('href'))
                                time.sleep(randomWaitTime)
                                driver.find_element_by_xpath('/html').send_keys(Keys.HOME)
                                driver.back()
                        except (NoSuchElementException, ElementClickInterceptedException):
                            print('Some error occured at the Seller Profile Page')
                        if check_exists_by_xpath(driver, '//*[@class="zgFirstRank"]/a'):
                            pyautogui.moveTo(driver.find_element_by_xpath('//*[@class="zgFirstRank"]/a').location['x'], driver.find_element_by_xpath('//*[@class="zgFirstRank"]/a').location['y'], 1)
                            top100 = driver.find_element_by_xpath('//*[@class="zgFirstRank"]/a').click()
                            time.sleep(randomWaitTime)
                            driver.back()
                        while True:
                            if not check_exists_by_xpath(driver, f'//div[@data-index="{i}" and @data-component-type="s-search-result"]'):
                                driver.back()
                                if driver.current_url == 'https://www.amazon.com/':
                                    i+=1
                                    driver.forward()
                            else:
                                break
                except (ElementNotInteractableException, NoSuchElementException):
                    with open(f'log_{date}.txt', 'a') as error_log:
                        error_log.write(f'Error occured on this URL: {driver.current_url}\n')
                        error_log.write(traceback.format_exc())
                    print("Some error occurred!")
                    driver.refresh()
                    print(traceback.format_exc())
                driver.close()
    except:
            with open(f'log_{date}.txt', 'a') as error_log:
                error_log.write(f'Error occured on this URL: {driver.current_url}\n')
                error_log.write(traceback.format_exc())
                
def addtocart():
    addtocartCSV = filedialog.askopenfilename(filetypes=([('CSV files', '*.csv')]))
    addcart_file = open(addtocartCSV)
    addcart_list = []
    for i in addcart_file:
        addcart_list.append(str(i).strip('\n'))
    addcart_file.close()
    add_cart = str(' '.join(addcart_list))
    for i in addcart_list:
             main_cart_list.append(i)
def addws():
    addtowsCSV = filedialog.askopenfilename(filetypes=([('CSV files', '*.csv')]))
    addws_file = open(addtowsCSV)
    addws_list = []
    for i in addws_file:
            addws_list.append(str(i).strip('\n'))
    addws_file.close()
    for i in addws_list:
            main_ws_list.append(i)
def surf():
         surfCSV = filedialog.askopenfilename(filetypes=([('CSV files', '*.csv')]))
         surf_file = open(surfCSV)
         surf_list = []
         for i in surf_file:
             surf_list.append(str(i).strip('\n'))
         surf_file.close()
         surf_ws = str(' '.join(surf_list))
         for i in surf_list:
             main_surf_list.append(i)
def keyword():
         global keywords_file
         keywordCSV = filedialog.askopenfilename(filetypes=([('CSV files', '*.csv')]))
         keyword_file = open(keywordCSV)
         keyword_list = []
         for i in keyword_file:
             keyword_list.append(i.strip('\n'))
         keyword_file.close()
         for i in keyword_list:
             main_keyword_list.append(i)
         
def profiles():
         global profile_file
         profileCSV = filedialog.askopenfilename(filetypes=([('CSV files', '*.csv')]))
         profile_file = open(profileCSV)
         profile_list = []
         for i in profile_file:
             profile_list.append(str(i).strip('\n'))
         profile_file.close()
         for i in profile_list:
             main_profile_list.append(i)
def check_xpath(driver,xpath):

        try:
            driver.find_element_by_xpath(xpath)
        except NoSuchElementException:
            return False
        return True
def stopprocess():
   for i in range(0,len(stopper)):
       if stopper[i].isAlive():
           stopper[i].kill()
           print("process killed")
       else:
           continue

def exit():
    sys.exit(0)

def CallME(profileid):
   try:

     chrome_options = Options()
     chrome_driver = r'chromedriver.exe'
     mla_url = 'http://127.0.0.1:35000/api/v1/profile/start?automation=true&profileId='+main_profile_list[profileid]
     resp = requests.get(mla_url)
     json = resp.json()
     chrome_options.add_experimental_option("debuggerAddress", json['value'][7:])
     driver = webdriver.Chrome(chrome_driver, options=chrome_options)
     driver.maximize_window()
     driver.minimize_window()
     driver.maximize_window()
     time.sleep(random.randint(4, 9))
     driver.get('https://www.amazon.com/')
     time.sleep(random.randint(4, 9))
     time.sleep(random.randint(4, 9))

     
     if (len(main_surf_list) != 0):
            time.sleep(random.randint(4, 9))
            driver.get(str(main_surf_list[profileid]))
            time.sleep(random.randint(4, 9))
            try:
                element = driver.find_element_by_id("aboutThisItem_atf_feature_div")
                actions = ActionChains(driver)
                actions.move_to_element(element).perform()
                time.sleep(random.randint(4, 9))
                try:
                    element2=driver.find_element_by_id("aw-udpv3-customer-reviews_feature_div")
                    time.sleep(random.randint(4, 9))
                    element2.click()
                            
                except NoSuchElementException:
                         print("NO reviews available")
                            
            except NoSuchElementException:
                 print("No details found for this")
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/16);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/10);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/9);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/8);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/6);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/5);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/4);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/3);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight/2);")
                 time.sleep(random.randint(4, 9))
                 driver.execute_script("window.scrollTo(0, document.body.scrollHeight);")
                 time.sleep(random.randint(4, 9))
                # search_box.send_keys(f'{main_keyword_list[i]}')
                # search_box.send_keys(Keys.RETURN)
                 time.sleep(random.randint(4, 9))
               
            #clickable = driver.find_elements_by_class_name("nav-input")
            #clickable.click()
     if (len(main_ws_list) != 0):
                    time.sleep(random.randint(4, 9))
                    driver.get(str(main_ws_list[profileid]))
                    time.sleep(random.randint(4, 9))
                    if check_xpath(driver, '//*[@id="add-to-wishlist-button-submit"]'):
                        try:
                            driver.find_element_by_xpath('//*[@id="add-to-wishlist-button-submit"]').click()
                            time.sleep(random.randint(4, 9))
                            action = webdriver.ActionChains(driver)
                            try:
                                time.sleep(random.randint(4, 9))
                                
                                ele = driver.find_element_by_id("atwl-popover-lists")

                               
                               
                                time.sleep(random.randint(4, 9))
                                ele.click()
                            except  NoSuchElementException:
                                print("Sorry nothing was found")

                            time.sleep(random.randint(4, 9))
                           

                        except ElementNotInteractableException:
                            print("")
                            

                # search_box.send_keys(f'{main_keyword_list[i]}')
                # search_box.send_keys(Keys.RETURN)
                        time.sleep(random.randint(4, 9))
     if(len(main_cart_list)!=0):
                    time.sleep(random.randint(4, 9))
                    driver.get(str(main_cart_list[profileid]))
                    time.sleep(random.randint(4, 9))
                    if check_xpath(driver, '//*[@id="add-to-cart-button"]'):
                        try:
                            driver.find_element_by_xpath('//*[@id="add-to-cart-button"]').click()
                            time.sleep(random.randint(4,9))
                            try:
                               element = driver.find_element_by_class_name("a-button-input")
                               actions_1 = ActionChains(driver)
                               time.sleep(2)
                               actions_1.move_to_element(element).perform().click()
                               time.sleep(3)
                            except Exception as e:
                               print("ERROR : "+str(e))
                               print("pop up not appeared")
                            time.sleep(random.randint(4, 9))
                        except ElementNotInteractableException:
                          time.sleep(random.randint(4, 9))

                        



                    time.sleep(random.randint(4, 9))

               

            
                
     time.sleep(random.randint(4, 9))
     driver.close()
   except:
       traceback.print_exc()
       driver.close()
def test(i):
    print("I was : ",i)
    
def run():
     stopper2=[]
     if (len(main_keyword_list) != 0):
         profiles = []
         profiles = str(' '.join(main_profile_list))
         threadsecond=[]
         main_user=entry.get("1.0","end-1c")
         run_out=int(main_user)
         start_one=0
         input_1=run_out
         while(run_out<len(main_profile_list)):
          temp_array_2=[]
          for j in range(start_one,run_out):
                 
                 threadq = 't'+str(j)
                 temp_array_2.append(threadq)
         
          start_one=run_out
          run_out+=input_1
          threadsecond.append(temp_array_2)
          my_1=0
          count_1=1
         while my_1<len(threadsecond):
           start_issue_1=[]
           for i in range(0,len(threadsecond[my_1])):
              threadsecond[my_1][i]=threading.Thread(target=main_bot, args=(profiles, main_keyword_list,count_1,))
              start_issue_1.append(threadsecond[my_1][i])
              stopper2.append(threadsecond[my_1][i])
              count_1+=1
           for i in range(0,len(start_issue_1)):
                 start_issue_1[i].start()
           for i in range(0,len(start_issue_1)):
                start_issue_1[i].join()
           start_issue_1.clear()
           time.sleep(3)
           my_1+=1
     if(len(main_cart_list)!=0 or len(main_surf_list)!=0 or len(main_ws_list)!=0):
      thread=[]
      user_entry=entry.get("1.0","end-1c")
      run_in=int(user_entry)
      start=0
      inp=run_in
         
      while(run_in<len(main_profile_list)):
          temp_array=[]
          for j in range(start,run_in):
                 
                 threadp = 't'+str(j)
                 temp_array.append(threadp)
         
          start=run_in
          run_in+=inp
          thread.append(temp_array)
      my=0
      count=1
      while my<len(thread):
          start_issue=[]
          for i in range(0,len(thread[my])):
              thread[my][i]=threading.Thread(target=CallME, args=(count,))
              start_issue.append(thread[my][i])
              stopper.append(thread[my][i])
              count+=1
          for i in range(0,len(start_issue)):
                   start_issue[i].start()
          for i in range(0,len(start_issue)):
               start_issue[i].join()
          start_issue.clear()
          time.sleep(3)
          my+=1
          print(my)

     #for i in range(start,run_in):
     #       threadname = 't'+str(i)
     #       threadname= threading.Thread(target=CallME, args=(i+1,))
     #       thread.append(threadname)
     #for i in range(0,len(thread)):
     #       thread[i].start()
        

def main():
     window.title("Amazon bot")
     window.geometry("850x700+300+-10")
     photo = PhotoImage(file = "my_assets/banner.png")
     photo1=PhotoImage(file = "my_assets/cart_btn.png")
     photo2=PhotoImage(file = "my_assets/ws_btn.png")
     photo3=PhotoImage(file = "my_assets/surt_btn.png")
     photo4=PhotoImage(file = "my_assets/button_run.png")
     photo5=PhotoImage(file = "my_assets/combo_btn_6.png")
     photo6=PhotoImage(file = "my_assets/profile_btn.png")
     photo7=PhotoImage(file = "my_assets/ontime.png")
     photo10 = PhotoImage(file="my_assets/top1.png")
     photo11 = PhotoImage(file="my_assets/top2.png")
     photo12 = PhotoImage(file="my_assets/top3.png")
     photo13 = PhotoImage(file="my_assets/button_stop-processes.png")
     photo14 = PhotoImage(file="my_assets/button_exit.png")


     label1=Label(window,image=photo,width=850,height=260)
     label1.place(x=0,y=0)
     add_cart = tkinter.Button(window, text="",image=photo1,bd="0",pady="10", command=lambda:addtocart())
     add_cart.place(x=300,y=390)
     add_ws = tkinter.Button(window, text="",image=photo2,bd="0",pady="10", command=lambda:addws())
     add_ws.place(x=300,y=320)
     link_surf = tkinter.Button(window, text="",image=photo3,bd="0",pady="10", command=lambda:surf())
     link_surf.place(x=300,y=460)
     add_keyword = tkinter.Button(window, text="",image=photo5,bd="0",pady="10", command=lambda:keyword())
     add_keyword.place(x=300,y=530)
     add_profile = tkinter.Button(window, text="",image=photo6,bd="0",pady="10", command=lambda:profiles())
     add_profile.place(x=300,y=600)

     global entry
     entry= Text(window,font=("Courier", 19, "italic"),width=10,height=2)
     entry.place(x=70,y=390)
     run_test = tkinter.Button(window, text="",image=photo4,bd="0",pady="10", command=lambda:run())
     run_test.place(x=590,y=370)

     label3 = Label(window, image=photo7)
     label3.place(x=60, y=320)


     label5 = Label(window, image=photo10)
     label5.place(x=20, y=260)
     label6 = Label(window, image=photo11)
     label6.place(x=290, y=260)
     label7 = Label(window, image=photo12)
     label7.place(x=560, y=260)
     stop_test = tkinter.Button(window, text="", image=photo13, bd="0", pady="10", command=lambda: stopprocess())
     stop_test.place(x=590, y=320)
     exit_test = tkinter.Button(window, text="", image=photo14, bd="0", pady="10", command=lambda: exit())
     exit_test.place(x=590, y=420)
    
     window.resizable(False,False)
     window.mainloop()
    
        
main()
