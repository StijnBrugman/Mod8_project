from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.action_chains import ActionChains
import time

start_date_list = (
    "1/1/1971", "1/1/1974", "1/1/1977", "1/1/1980", "1/1/1983", "1/1/1986", "1/1/1989", "1/1/1992", "1/1/1995",
    "1/1/1998", "1/1/2001", "1/1/2004", "1/1/2007", "1/1/2010", "1/1/2013", "1/1/2016", "1/1/2019")

end_date_list = (
    "31/12/1973", "31/12/1976", "31/12/1979", "31/12/1982", "31/12/1985", "31/12/1988", "31/12/1991", "31/12/1994",
    "31/12/1997", "31/12/2000", "31/12/2003", "31/12/2006", "31/12/2009", "31/12/2012", "31/12/2015", "31/12/2018",
    "31/12/2020")

# start_date_list = (
#     "1/1/1950", "1/1/1953", "1/1/1956", "1/1/1959", "1/1/1962", "1/1/1965", "1/1/1968", "1/1/1971", "1/1/1974",
#     "1/1/1977", "1/1/1980", "1/1/1983", "1/1/1986", "1/1/1989", "1/1/1992", "1/1/1995", "1/1/1998", "1/1/2001",
#     "1/1/2004", "1/1/2007", "1/1/2010", "1/1/2013", "1/1/2016", "1/1/2019")
#
# end_date_list = (
#     "31/12/1952", "31/12/1955", "31/12/1958", "31/12/1961", "31/12/1964", "31/12/1967", "31/12/1970", "31/12/1973",
#     "31/12/1976", "31/12/1979", "31/12/1982", "31/12/1985", "31/12/1988", "31/12/1991", "31/12/1994", "31/12/1997",
#     "31/12/2000", "31/12/2003", "31/12/2006", "31/12/2009", "31/12/2012", "31/12/2015", "31/12/2018", "31/12/2020")

for j in range(len(start_date_list)):
    driver = webdriver.Chrome("chromedriver.exe")
    actions = ActionChains(driver)

    driver.get("https://waterinfo.rws.nl/#!/nav/index/")
    time.sleep(2)
    more_data = driver.find_element_by_xpath("/html/body/nav/div[1]/div[2]/ul/li[2]/button").click()
    time.sleep(2)
    waterkwantiteit = driver.find_element_by_xpath(
        "/html/body/nav/div[4]/div[7]/div[1]/div[1]/form/ul/li[2]/button[1]").click()
    time.sleep(1)
    waterhoogten = driver.find_element_by_xpath(
        "/html/body/nav/div[4]/div[7]/div[1]/div[1]/form/ul/li[2]/ul/li[5]/button").click()
    time.sleep(1)
    nap = driver.find_element_by_xpath(
        "/html/body/nav/div[4]/div[7]/div[1]/div[1]/form/ul/li[2]/ul/li[5]/ul/li[10]/label").click()
    time.sleep(1)
    verder = driver.find_element_by_xpath("/html/body/nav/div[4]/div[7]/div[1]/div[3]/button[2]").click()
    time.sleep(1)

    start_date = driver.find_element_by_xpath('//*[@id="date-from"]').click()
    time.sleep(1)
    start_dates = driver.find_element_by_xpath('//*[@id="date-from"]')
    start_dates.send_keys(start_date_list[j])
    time.sleep(1.5)

    end_date = driver.find_element_by_xpath('//*[@id="date-to"]').click()
    time.sleep(1)
    end_date = driver.find_element_by_xpath('//*[@id="date-to"]').click()
    end_dates = driver.find_element_by_xpath('//*[@id="date-to"]')
    end_dates.send_keys(end_date_list[j])
    time.sleep(.5)
    end_dates.send_keys(Keys.ENTER)
    time.sleep(1)
    uit_lijst = driver.find_element_by_xpath("/html/body/nav/div[4]/div[7]/div[2]/button[2]").click()
    for i in range(20):
        try:
            driver.find_element_by_xpath('//*[@id="q"]')
            break
        except:
            time.sleep(5)
            i += 1

    search = driver.find_element_by_xpath('//*[@id="q"]').click()
    searches = driver.find_element_by_xpath('//*[@id="q"]')
    time.sleep(1)
    searches.send_keys("ijmuiden Noordersluis")
    time.sleep(2)
    try:
        driver.find_element_by_xpath('//*[@id="list-location-checkbox-IJmuiden-Noordersluis(IJMDNDSS)"]').click()
        time.sleep(2)
        volgende = driver.find_element_by_xpath("/html/body/div[18]/button[4]").click()
        time.sleep(3)
        email = driver.find_element_by_xpath('//*[@id="tsubmission"]').click()
        time.sleep(.5)
        email_add = driver.find_element_by_xpath('//*[@id="tsubmission"]')
        email_add.send_keys("david.lammers88@gmail.com")
        time.sleep(.5)
        email_add.send_keys(Keys.ENTER)
        time.sleep(3)

        driver.close()
        time.sleep(1)
    except:
        print(str(start_date_list[j]) + " " + str(end_date_list[j]) + " not available")
        time.sleep(2)
        driver.close()
        time.sleep(1)

    # time.sleep(2)
    # volgende = driver.find_element_by_xpath("/html/body/div[18]/button[4]").click()
    # time.sleep(3)
    # email = driver.find_element_by_xpath('//*[@id="tsubmission"]').click()
    # time.sleep(.5)
    # email_add = driver.find_element_by_xpath('//*[@id="tsubmission"]')
    # email_add.send_keys("david.lammers88@gmail.com")
    # time.sleep(.5)
    # email_add.send_keys(Keys.ENTER)
    # time.sleep(3)
    #
    # driver.close()
    # time.sleep(1)

