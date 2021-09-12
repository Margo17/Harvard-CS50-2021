-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Who is the thief?
-- What city the thief escaped to?
-- Who is the accomplice who helped thief to escape?
-- FIRST INFO: Theft took place on July 28, on Chamberlin Street.

-- First I'm looking at the crime scene reports to find out more about the incident:
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- CLUE:
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present
-- at the time — each of their interview transcripts mentions the courthouse.

-- I should inspect the courthouse security logs on July 28th 10:15am:
SELECT activity, license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute = 15;

-- No logs at 10:15 found.

-- Based on the crime scene description it looks that the witness interviews with courthouse mentions could prove useful:
SELECT name, transcript
FROM interviews
WHERE month = 7 AND day = 28 AND transcript LIKE "%courthouse%";

-- CLUE:
-- Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

-- USEFUL INFO:
-- Check security logs from 10:15 - 10:25 for car licenses. +
-- Thief withdrew money from an ATM on Fifer Street earlier that morning.
-- Thief is taking the earliest flight out of Fiftyville on July 29th. +

-- Ok, so earliest flight is a good lead, lets check it:
SELECT *
FROM flights
WHERE origin_airport_id = 8 AND month = 7 AND day = 29
ORDER BY hour
LIMIT 1;

-- CLUE:
-- Criminal went to Heathrow, London, flight id 36.

-- Lets take the flight passenger data:
SELECT passport_number, seat
FROM passengers
WHERE flight_id =
(SELECT id
FROM flights
WHERE month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1);

-- CLUE:
-- passport_number | seat
-- 7214083635 | 2A
-- 1695452385 | 3B
-- 5773159633 | 4A
-- 1540955065 | 5C
-- 8294398571 | 6C
-- 1988161715 | 6D
-- 9878712108 | 7A
-- 8496433585 | 7B

-- Lets look to whom these passport numbers belong to:
SELECT name, license_plate
FROM people
WHERE passport_number IN
(SELECT passport_number
FROM passengers
WHERE flight_id =
(SELECT id
FROM flights
WHERE month = 7 AND day = 29
ORDER BY hour, minute
LIMIT 1));

-- CLUE:
-- People who were in the flight to Heathrow:
-- name | license_plate
-- Bobby | 30G67EN
-- Roger | G412CB7 <- SUS
-- Madison | 1106N58
-- Danielle | 4328GD8 <- SUS
-- Evelyn | 0NTHK55 <- SUS
-- Edward | 130LD9Z
-- Ernest | 94KL13X <- SUS
-- Doris | M51FA04

-- Lets see which of these cars left the parking lot as according to a witness:
SELECT activity, license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute < 15 AND minute > 5;

-- Result no suspects match the license_plates.
-- activity | license_plate
-- entrance | R3G7486
-- entrance | 13FNH73

-- Lets see who owns these cars:
SELECT id, name
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute < 15 AND minute > 5);

-- These cars belong to:
-- id | name
-- 325548 | Brandon
-- 745650 | Sophia

-- Maybe transaction info will provide with any clues:
SELECT *
FROM atm_transactions
WHERE atm_location = "Fifer Street" AND transaction_type = "withdraw";

-- Lets try to link account numbers with people whos cars have been spoted at the crime scene:
SELECT account_number
FROM bank_accounts
WHERE person_id IN
(SELECT id
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute < 15 AND minute > 5));

-- CLUE:
-- Provided accounts of suspects who left the crime scene with cars:
-- account_number
-- 42445987
-- 86850293

-- Ok, now analyse if these acc numbers made withdrawals in the morning of the fateful day:
SELECT id
FROM atm_transactions
WHERE account_number IN
(SELECT account_number
FROM bank_accounts
WHERE person_id IN
(SELECT id
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute < 15 AND minute > 5)))
AND atm_location = "Fifer Street" AND transaction_type = "withdraw";

-- My suspect is ID 1109 with account number - 86850293! He made withdrawal and also escaped the parking lot by car. Raymond helped the thief by lying in the interview.
-- Lets see who is the culprit of this mess!
SELECT name
FROM people
WHERE id =
(SELECT person_id
FROM bank_accounts
WHERE account_number = 86850293);

-- It's Brandon!

-- NOT.

-- OK. Lets try again.

-- Let's see who sat together in a plane. There will be two pairs of suspects, and one pair is the thief and the accomplice:
SELECT name, passport_number
FROM people
WHERE passport_number IN
(8294398571, 1988161715, 9878712108, 8496433585);

-- Result:
-- name | passport_number
-- Bobby | 9878712108
-- Madison | 1988161715
-- Danielle | 8496433585
-- Evelyn | 8294398571

-- According to the plane seats the suspects are either Bobby and Danielle or Madison and Evelyn.

-- Maybe the suspects called each other after the robbery, this querie gets the number of the receiver:
SELECT receiver
FROM phone_calls
WHERE caller =
(SELECT phone_number
FROM people
WHERE passport_number =
(SELECT passport_number
FROM people
WHERE name = "Roger"))
AND month = 7 AND day = 28 AND duration < 60;

-- Identify receiver:
SELECT name
FROM people
WHERE phone_number =
(SELECT receiver
FROM phone_calls
WHERE caller =
(SELECT phone_number
FROM people
WHERE passport_number =
(SELECT passport_number
FROM people
WHERE name = "Ernest"))
AND month = 7 AND day = 28 AND duration < 60);

-- No luck... Receivers where all different and not from plane passengers.

-- OK. Lets see who left the parking lot as according to a witness:
SELECT activity, license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit";

-- Now. Who owns these cars?:
SELECT name
FROM people
WHERE license_plate IN
(SELECT license_plate
FROM courthouse_security_logs
WHERE month = 7 AND day = 28 AND hour  = 10 AND minute >= 15 AND minute <= 25 AND activity = "exit");

-- RESULT: NEW SUSPECTS are Patrick, Amber, Elizabeth, Roger, Danielle, Russell, Evelyn, Ernest.
-- The ones that flew to Heathrow are - Roger, Danielle, Evelyn, Ernest.
--- Ernest appearing everywhere so he is the prime suspect!

-- Lets check the calls again via query written earlier.
SELECT name
FROM people
WHERE phone_number =
(SELECT receiver
FROM phone_calls
WHERE caller =
(SELECT phone_number
FROM people
WHERE passport_number =
(SELECT passport_number
FROM people
WHERE name = "Ernest"))
AND month = 7 AND day = 28 AND duration < 60);

--- And the receiver is Berthold, he must be the accomplice.