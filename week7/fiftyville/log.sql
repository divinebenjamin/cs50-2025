-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Get details on the report
SELECT * FROM crime_scene_reports 
WHERE day = 28 AND month = 7 AND street = 'Humphrey Street';
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.

-- Find more info from the three witnesses
SELECT * FROM interviews 
WHERE transcript LIKE '%bakery%';
-- Ruth - Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene - I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
-- Raymond - As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- RUTH 
-- Check camera log within the timeframe ruth pointed out
SELECT * FROM bakery_security_logs 
WHERE day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25);
-- 260|2024|7|28|10|16|exit|5P2BI95
-- 261|2024|7|28|10|18|exit|94KL13X
-- 262|2024|7|28|10|18|exit|6P58WS2
-- 263|2024|7|28|10|19|exit|4328GD8
-- 264|2024|7|28|10|20|exit|G412CB7
-- 265|2024|7|28|10|21|exit|L93JTIZ
-- 266|2024|7|28|10|23|exit|322W7JE
-- 267|2024|7|28|10|23|exit|0NTHK55

-- Checking the names of people with the licence_plate that left within the time frame
SELECT * FROM people 
WHERE license_plate IN 
  (SELECT license_plate from bakery_security_logs 
  WHERE day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25));
-- 221103|Vanessa|(725) 555-4692|2963008352|5P2BI95
-- 243696|Barry|(301) 555-4174|7526138472|6P58WS2
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 398010|Sofia|(130) 555-0289|1695452385|G412CB7
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 560886|Kelsey|(499) 555-9472|8294398571|0NTHK55
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X

-- Eugene
-- Check the transactions at Leggett Street earlier that morning
SELECT * FROM atm_transactions 
WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7;
-- 46|28500762|2024|7|28|Leggett Street|withdraw|48
-- 64|28296815|2024|7|28|Leggett Street|withdraw|20
-- 66|76054385|2024|7|28|Leggett Street|withdraw|60
-- 67|49610011|2024|7|28|Leggett Street|withdraw|50
-- 69|16153065|2024|7|28|Leggett Street|withdraw|80
-- 75|86363979|2024|7|28|Leggett Street|deposit|10
-- 88|25506511|2024|7|28|Leggett Street|withdraw|20
-- 13|81061156|2024|7|28|Leggett Street|withdraw|30
-- 36|26013199|2024|7|28|Leggett Street|withdraw|35

-- Check the account number with the bank to get the names of people
SELECT * FROM people 
WHERE id IN 
  (SELECT person_id FROM bank_accounts 
  WHERE account_number IN 
    (SELECT account_number FROM atm_transactions 
    WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7));
-- 395717|Kenny|(826) 555-1652|9878712108|30G67EN
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 438727|Benista|(338) 555-6650|9586786673|8X428L0
-- 449774|Taylor|(286) 555-6063|1988161715|1106N58
-- 458378|Brooke|(122) 555-4581|4408372428|QX4YZN3
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X
-- 948985|Kaelyn|(098) 555-1164|8304650265|I449449

-- GET THE PRIMARY SUSPECTS - people that fall under Ruth and Eugene interview
SELECT * FROM people 
WHERE license_plate IN 
  (SELECT license_plate from bakery_security_logs 
  WHERE day = 28 AND hour = 10 AND (minute >= 15 AND minute <= 25))
AND id IN 
  (SELECT person_id FROM bank_accounts 
  WHERE account_number IN 
    (SELECT account_number FROM atm_transactions 
    WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7));
-- 396669|Iman|(829) 555-5269|7049073643|L93JTIZ
-- 467400|Luca|(389) 555-5198|8496433585|4328GD8
-- 514354|Diana|(770) 555-1861|3592750733|322W7JE
-- 686048|Bruce|(367) 555-5533|5773159633|94KL13X
-- Iman, Luca, Diana, Bruce


-- Raymond
-- based on the suspects find out who made a call for less than a min after 10:15 on that day
SELECT * FROM phone_calls 
WHERE caller IN 
  ('(829) 555-5269', '(389) 555-5198', '(770) 555-1861', '(367) 555-5533') 
AND day = 28 AND month = 7 AND duration <= 60;
-- 233|(367) 555-5533|(375) 555-8161|2024|7|28|45
-- 255|(770) 555-1861|(725) 555-3243|2024|7|28|49

-- NARROWED SUSPECTS
-- Bruce and Diana

-- find out who they called
SELECT * FROM people 
WHERE phone_number IN 
    (SELECT receiver FROM phone_calls 
  WHERE caller IN 
    ('(829) 555-5269', '(389) 555-5198', '(770) 555-1861', '(367) 555-5533') 
  AND day = 28 AND month = 7 AND duration <= 60);
-- 847116|Philip|(725) 555-3243|3391710505|GW362R6
-- 864400|Robin|(375) 555-8161||4V16VO0

-- PRIMARY ACOMPLICE
-- Philip and Robin

-- Check transaction made by the receiver after the call
SELECT * FROM atm_transactions 
WHERE account_number IN 
  (SELECT account_number FROM bank_accounts
  WHERE person_id IN 
    (SELECT id FROM people 
    WHERE phone_number IN 
      (SELECT receiver FROM phone_calls 
      WHERE caller IN 
        ('(829) 555-5269', '(389) 555-5198', '(770) 555-1861', '(367) 555-5533') 
      AND day = 28 AND month = 7 AND duration <= 60)))
AND day IN (28, 29) and month = 7;
-- 417|94751264|2024|7|29|Blumberg Boulevard|deposit|90
-- 494|47746428|2024|7|29|Leggett Street|deposit|15
-- 548|47746428|2024|7|29|Daboin Sanchez Drive|withdraw|60

-- Check name of peple with the accound number
SELECT * FROM people 
WHERE id IN 
  (SELECT person_id FROM bank_accounts
  WHERE account_number IN 
  (94751264, 47746428));
-- 847116|Philip|(725) 555-3243|3391710505|GW362R6
-- 864400|Robin|(375) 555-8161||4V16VO0
-- Still Philip and Robin but Robin does not have a passport 

-- Check flights that left ealier the next day
SELECT * FROM flights 
WHERE day = 29 AND month = 7 AND hour <= 12;

-- check the passport_numbers for the suspects that and accomplice that left earlier the next day
SELECT name FROM people
WHERE passport_number IN 
  (3391710505, 3592750733, 5773159633) ;