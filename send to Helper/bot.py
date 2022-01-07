from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains
from selenium.common.exceptions import ElementClickInterceptedException, NoSuchElementException, ElementNotInteractableException, StaleElementReferenceException
from datetime import datetime
import time
import random     
import requests
import traceback
import pyautogui
import os

pyautogui.FAILSAFE = False

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


def main_bot(profiles,keywords):
    '''
    This class contains all the functionalities of the bot to visit Amazon
    '''
    #mla_profile_id = profiles.split()
    try:
            date = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
            max_wait_time = 7
            randomWaitTime = random.randint(3, max_wait_time)
            # mla_profile_id = ['9527B281-92A2-47BD-83C1-DA2682051A84', 'D203BDF3-278F-432F-9E69-A01427439776']

            # for profile in mla_profile_id:
            # mla_url = 'http://127.0.0.1:35000/api/v1/profile/start?automation=true&profileId='+mla_profile_id[profile_id]
            # resp = requests.get(mla_url)
            # json = resp.json()
            # print(json)
            chrome_options = Options()
          #  chrome_options.add_experimental_option("debuggerAddress", json['value'][7:])
            chrome_driver = r'C:/Users/Hp/AppData/Local/Temp/Rar$EXa12748.016/chromedriver.exe'
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

# Calling the function we have made above
mla_profile_id = ['536A39CB-21D4-4101-AFA9-C6DB6617CB5A', 'F70E3F39-6035-4DAA-A473-79002AC44E76', 'DEC660D5-96E1-43C4-A5A1-F4F8AD1B44F2', '24F4B506-0C75-46F4-8D4C-F98BCCDA8700']
profiles_input = input('Enter all the profiles separated by space: ')
#mla_profile_id = profiles_input.split()
main_bot(mla_profile_id, ['keyboard', 'laptop'])
