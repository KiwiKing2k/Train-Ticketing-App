import java.util.regex.Pattern
import java.io.File
import java.util.Scanner

data class Seat(
    val seatNumber: Int,
    var reserved: Boolean = false
)

data class SeatInfo(
    val seatNumber: Int,
    val wagonNumber: Int
)

data class Credentials(
    val username: String,
    val password: String
)

fun isValidDateFormat(date: String): Boolean {
    val pattern = Pattern.compile("\\d{1,2}[\\./\\-_ ]\\d{2}[\\./\\-_ ]\\d{4}")
    return pattern.matcher(date).matches()
}

fun isValidDate(date: String): Boolean {
    val sep = when {
        date.contains('-') -> '-'
        date.contains('_') -> '_'
        date.contains('.') -> '.'
        date.contains('/') -> '/'
        else -> ' '
    }
    val parts = date.split(sep)
    if (parts.size != 3) throw IllegalArgumentException("Invalid date format.")
    val day = parts[0].toInt()
    val month = parts[1].toInt()
    val year = parts[2].toInt()

    if (year < 2025) throw IllegalArgumentException("Year must be 2025 or later.")
    if (month !in 1..12) throw IllegalArgumentException("Month must be between 1 and 12.")
    if (day !in 1..31) throw IllegalArgumentException("Day must be between 1 and 31.")

    // Check for months with 30 days
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) {
        throw IllegalArgumentException("Invalid day for the given month.")
    }

    // Check for February
    if (month == 2) {
        val isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)
        if (day > 29 || (day == 29 && !isLeapYear)) {
            throw IllegalArgumentException("Invalid day for February.")
        }
    }

    return true
}

fun isValidTime(time: String): Boolean {
    val timePattern = Pattern.compile("([01]?[0-9]|2[0-3]):[0-5][0-9]")
    if (!timePattern.matcher(time).matches()) {
        throw IllegalArgumentException("Invalid time format.")
    }
    return true
}

fun isValidCityName(cityName: String): Boolean {
    val cityPattern = Pattern.compile("^[A-Z][a-zA-Z\\- ]*$")
    return cityPattern.matcher(cityName).matches()
}

fun generateKey(str: String, key: String): String {
    val x = str.length
    val keyBuilder = StringBuilder(key)
    var i = 0
    while (keyBuilder.length < x) {
        if (i == x) i = 0
        keyBuilder.append(keyBuilder[i])
        i++
    }
    return keyBuilder.toString()
}

fun cipherText(str: String, key: String): String {
    val cipherText = StringBuilder()
    for (i in str.indices) {
        val x = (str[i].code + key[i].code - 2 * 32) % 95 + 32
        cipherText.append(x.toChar())
    }
    return cipherText.toString()
}

fun originalText(cipherText: String, key: String): String {
    val og_text = StringBuilder()
    for (i in cipherText.indices) {
        val x = (cipherText[i].code - key[i].code + 95) % 95 + 32 //this has caused problems
        og_text.append(x.toChar())
    }
    return og_text.toString()
}

fun getPasswordSecurityLevel(password: String): Int {
    var has_upper = false
    var has_lower = false
    var has_digit = false
    var has_punct = false

    for (c in password) {
        if (c.isUpperCase()) has_upper = true
        if (c.isLowerCase()) has_lower = true
        if (c.isDigit()) has_digit = true
        if (c in "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~") has_punct = true
    }

    var securityLevel = 0
    if (has_lower) securityLevel++
    if (has_upper) securityLevel++
    if (has_digit) securityLevel++
    if (has_punct) securityLevel++
    if (password.length >= 8) securityLevel++

    return when {
        securityLevel == 5 -> {
            println("Password is good")
            2
        }

        securityLevel >= 3 -> {
            println("Password is ok")
            1
        }

        else -> throw IllegalArgumentException("Password is weak")
    }
}

class Wagon {
    private var classType: Int = 0 // 1 or 2
    private val maxCapacity: Int = 80 // standard for CFR
    private val seats: Array<Seat> = Array(maxCapacity) { Seat(it + 1, false) }
    private var reservedSeats: Int = 0

    fun wagonAssigner(classType: Int) {
        this.classType = classType
        reservedSeats = 0
        for (i in seats.indices) {
            seats[i] = Seat(i + 1, false)
        }
    }

    fun reserveAnySeat(): Int {
        if (reservedSeats < maxCapacity) {
            for (i in seats.indices) {
                if (!seats[i].reserved) {
                    seats[i].reserved = true
                    reservedSeats++
                    return i + 1
                }
            }
        }
        return -1
    }

    fun reserveSeat(seatNumber: Int): Int {
        if (seatNumber in 1..maxCapacity) {
            if (!seats[seatNumber - 1].reserved) {
                seats[seatNumber - 1].reserved = true
                reservedSeats++
                return seatNumber
            }
        }
        return -1
    }

    fun seeFreeSeats() {
        for (seat in seats) {
            if (!seat.reserved) {
                print("${seat.seatNumber} ")
            }
        }
        println()
    }

    fun seeReservedSeats() {
        for (seat in seats) {
            if (seat.reserved) {
                print("${seat.seatNumber} ")
            }
        }
        println()
    }

    fun getClassType(): Int {
        return classType
    }
}

class TrainRide(
    private val name: String,
    private val date: String,
    private val time: String,
    private val destination: String,
    private val origin: String,
    firstClassWagons: Int,
    secondClassWagons: Int
) {
    private val wagons: Array<Wagon> = Array(firstClassWagons + secondClassWagons) { Wagon() }
    private val firstClass: Int = firstClassWagons
    private val secondClass: Int = secondClassWagons

    init {
        if (!isValidDateFormat(date)) {
            throw IllegalArgumentException("Invalid date format.")
        }

        try {
            isValidDate(date)
        } catch (e: IllegalArgumentException) {
            throw e
        }

        try {
            isValidTime(time)
        } catch (e: IllegalArgumentException) {
            throw e
        }

        if (!isValidCityName(destination)) {
            throw IllegalArgumentException("Invalid destination city name.")
        }
        if (!isValidCityName(origin)) {
            throw IllegalArgumentException("Invalid origin city name.")
        }

        for (i in 0 until firstClassWagons) {
            wagons[i].wagonAssigner(1)
        }
        for (i in firstClassWagons until firstClassWagons + secondClassWagons) {
            wagons[i].wagonAssigner(2)
        }
    }

    fun reserveAnySeat(classType: Int): SeatInfo {
        val wagonsNr = if (classType == 1) firstClass else secondClass
        for (i in 0 until wagonsNr) {
            if (wagons[i].getClassType() == classType) {
                val seatNumber = wagons[i].reserveAnySeat()
                if (seatNumber != -1) {
                    return SeatInfo(seatNumber, i)
                }
            }
        }
        throw IllegalArgumentException("No available seats.")
    }

    fun reserveSpecificSeat(wagonNumber: Int, seatNumber: Int): Int {
        if (wagonNumber < 0 || wagonNumber >= firstClass + secondClass) {
            throw IllegalArgumentException("Invalid wagon number.")
        }
        if (wagons[wagonNumber].reserveSeat(seatNumber) == -1) {
            throw IllegalArgumentException("Seat already reserved.")
        }
        return 1
    }

    fun findReservedSeats() {
        val fileName = "../Data/Trains/$name.csv"
        val file = File(fileName)
        if (!file.exists()) {
            throw IllegalArgumentException("File not found.")
        }
        file.forEachLine { line ->
            if (line.isNotEmpty()) {
                val parts = line.split(',')
                val wagonNumber = parts[0].toInt()
                val seatNumber = parts[1].toInt()
                reserveSpecificSeat(wagonNumber, seatNumber)
            }
        }
    }
}

class Operator(private var username: String, private var password: String) {
    private var authenticated: Boolean = false

    fun login(username: String, password: String, secretPassword: String): Int {
        val password_full_caps = password.uppercase()
        val key = generateKey(password_full_caps, secretPassword)
        val file = File("../Data/op_login.txt")
        if (!file.exists()) {
            throw IllegalArgumentException("Login File not found")
        }
        val adminCred = mutableListOf<Credentials>()
        file.forEachLine { line ->
            val parts = line.split(',')
            val credUsername = parts[0]
            val encryptedPassword = parts[1]
            val credPassword = originalText(encryptedPassword, key).uppercase()
            adminCred.add(Credentials(credUsername, credPassword))
        }
        for (cred in adminCred) {
            if (cred.username == username && cred.password == password_full_caps) {
                authenticated = true
                return 1
            }
        }
        if (!authenticated) {
            throw IllegalArgumentException("Invalid credentials")
        }
        return 0
    }

    fun addRide() {
        if (!authenticated) {
            throw IllegalArgumentException("Not authenticated")
        }
        val scanner = Scanner(System.`in`)
        println("Enter ride name:")
        val name = scanner.nextLine()
        println("Enter date:")
        val date = scanner.nextLine()
        println("Enter time:")
        val time = scanner.nextLine()
        println("Enter start city:")
        val start = scanner.nextLine()
        println("Enter end city:")
        val end = scanner.nextLine()
        println("Enter number of first class wagons:")
        val firstClassWagons = scanner.nextInt()
        println("Enter number of second class wagons:")
        val secondClassWagons = scanner.nextInt()

        val ride = TrainRide(name, date, time, start, end, firstClassWagons, secondClassWagons)

        val file = File("../Data/rides.txt")
        file.appendText("$name,$date,$time,$start,$end,$firstClassWagons,$secondClassWagons\n")

        val fileName = "../Data/Trains/$name.csv"
        File(fileName).createNewFile()
    }

    fun removeRide() {
        if (!authenticated) {
            throw IllegalArgumentException("Not authenticated")
        }
        val scanner = Scanner(System.`in`)
        println("Enter ride name to remove:")
        val name = scanner.nextLine()

        val file = File("../Data/rides.txt")
        if (!file.exists()) {
            throw IllegalArgumentException("File not found")
        }
        val lines = file.readLines().filter { !it.contains(name) }
        if (lines.size == file.readLines().size) {
            throw IllegalArgumentException("Ride not found")
        }
        file.writeText(lines.joinToString("\n"))

        val fileName = "../Data/Trains/$name.csv"
        val trainFile = File(fileName)
        if (!trainFile.delete()) {
            println("Error deleting file")
        }
    }
}

class User(private var username: String, private var password: String) {
    private var authenticated: Boolean = false

    fun login(username: String, password: String, secretPassword: String): Int {
        val upperPassword = password.uppercase()
        val file = File("../Data/user_login.txt")
        if (!file.exists()) {
            throw IllegalArgumentException("Login File not found")
        }
        val userCred = mutableListOf<Credentials>()
        file.forEachLine { line ->
            val parts = line.split(',')
            val credUsername = parts[0]
            val encryptedPassword = parts[1]
            val key = generateKey(upperPassword, secretPassword)
            val credPassword = originalText(encryptedPassword, key).uppercase()
            userCred.add(Credentials(credUsername, credPassword))
        }
        for (cred in userCred) {
            if (cred.username == username && cred.password == upperPassword) {
                authenticated = true
                return 1
            }
        }
        if (!authenticated) {
            throw IllegalArgumentException("Invalid credentials")
        }
        return 0
    }

    fun authentification(secretPassword: String): Int {
        val scanner = Scanner(System.`in`)
        println("Enter name:")
        val name = scanner.nextLine()
        this.username = name
        println("Enter password:")
        val password = scanner.nextLine()
        try {
            getPasswordSecurityLevel(password)
        } catch (e: IllegalArgumentException) {
            throw e
        }

        this.password = password
        val fileRead = File("../Data/user_login.txt")
        if (!fileRead.exists()) {
            throw IllegalArgumentException("File not found")
        }
        fileRead.forEachLine { line ->
            if (line.contains(name)) {
                throw IllegalArgumentException("User already exists")
            }
        }

        val file = File("../Data/user_login.txt")
        val key = generateKey(password, secretPassword)
        file.appendText("$name,${cipherText(password, key)}\n")

        return 1
    }

    fun searchRide(origin: String, destination: String) {
        val file = File("../Data/rides.txt")
        if (!file.exists()) {
            throw IllegalArgumentException("File not found")
        }
        var found = false
        file.forEachLine { line ->
            val parts = line.split(',')
            val name = parts[0]
            val date = parts[1]
            val time = parts[2]
            val start = parts[3]
            val end = parts[4]
            if (start == origin && end == destination) {
                println("Ride found")
                println("Name: $name")
                println("Date: $date")
                println("Time: $time")
                println("Start: $start")
                println("End: $end")
                found = true
            }
        }
        if (!found) {
            throw IllegalArgumentException("Ride not found")
        }
    }

    fun searchRideByName(trainName: String): TrainRide {
        val file = File("../Data/rides.txt")
        if (!file.exists()) {
            throw IllegalArgumentException("File not found")
        }
        for (line in file.readLines()) {
            val parts = line.split(',')
            val name = parts[0]
            if (name == trainName) {
                val date = parts[1]
                val time = parts[2]
                val start = parts[3]
                val end = parts[4]
                val firstClassWagons = parts[5].toInt()
                val secondClassWagons = parts[6].toInt()
                return TrainRide(name, date, time, end, start, firstClassWagons, secondClassWagons)
            }
        }
        throw IllegalArgumentException("Ride not found")
    }

    fun buyTicket(trainName: String, classType: Int): Int {
        if (!authenticated) {
            throw IllegalArgumentException("Not authenticated")
        }
        val foundRide = searchRideByName(trainName)
        foundRide.findReservedSeats()
        val seat = foundRide.reserveAnySeat(classType)
        println("Seat reserved: ${seat.seatNumber} in wagon ${seat.wagonNumber + 1}")
        val file = File("../Data/Trains/$trainName.csv")
        file.appendText("${seat.wagonNumber},${seat.seatNumber},$username\n")
        return 1
    }
}

fun main() {

    val secretPassword = "ILOVEC"
    println("Welcome to the TrainRide application")

    var loggedIn = false

    println("Please login to continue")
    println("If you are a user type 1")
    println("If you are an operator type 0")
    val choice = readLine()!!.toInt()
    if (choice == 0) { // Operator
        while (!loggedIn) { // login attempt
            try {
                println("Enter name:")
                val name = readLine()!!
                println("Enter password (at least 6 characters):")
                val password = readLine()!!
                val smoothOperator = Operator(name, password)
                smoothOperator.login(name, password, secretPassword)
                println("Logged in")
                loggedIn = true

                // operation loops
                var continueOperation = 1
                while (continueOperation == 1) {
                    println("If you want to add a ride type 1")
                    println("If you want to remove a ride type 0")
                    val choice1 = readLine()!!.toInt()

                    if (choice1 == 1) { // add ride
                        try {
                            smoothOperator.addRide()
                        } catch (e: IllegalArgumentException) {
                            println(e.message)
                        }
                    } else { // remove ride
                        try {
                            smoothOperator.removeRide()
                        } catch (e: IllegalArgumentException) {
                            println(e.message)
                        }
                    }
                    println("If you want to continue type 1")
                    println("If you want to exit type 0")
                    continueOperation = readLine()!!.toInt()
                }
            } catch (e: IllegalArgumentException) {
                println(e.message)
                println("Please try again")
            }
        }
    } else { // User
        println("If you are a new user type 1")
        println("If you are an existing user type 2")
        val choice1 = readLine()!!.toInt()
        if (choice1 == 1) { // new user
            var continueOperation = 1
            while (continueOperation == 1) {
                val user = User("", "")
                try {
                    user.authentification(secretPassword)
                    continueOperation = 0
                } catch (e: IllegalArgumentException) {
                    println(e.message)
                    println("Please try again")
                    println("Enter 1 to continue or 0 to exit")
                    continueOperation = readLine()!!.toInt()
                    if (continueOperation == 0) {
                        return
                    }
                }
            }
            println("User created")
        }

        println("Please login to continue")

        while (!loggedIn) { // login loop
            try {
                println("Enter name:")
                val name = readLine()!!
                println("Enter password:")
                val password = readLine()!!
                val user = User(name, password)
                user.login(name, password, secretPassword)
                println("Logged in")
                loggedIn = true

                println("If you want to search for a ride type 1")
                println("If you want to buy a ticket type 2")
                println("If you want to exit type 0")
                var choice2 = readLine()!!.toInt()

                while (choice2 != 0) { // continue
                    if (choice2 == 1) {
                        println("Enter origin city:")
                        val origin = readLine()!!
                        println("Enter destination city:")
                        val destination = readLine()!!
                        try {
                            user.searchRide(origin, destination)
                        } catch (e: IllegalArgumentException) {
                            println(e.message)
                        }
                    } else if (choice2 == 2) {
                        println("Enter train name:")
                        val trainName = readLine()!!
                        println("Enter class type (1 or 2):")
                        val classType = readLine()!!.toInt()
                        try {
                            user.buyTicket(trainName, classType)
                        } catch (e: IllegalArgumentException) {
                            println(e.message)
                        }
                    }
                    println("If you want to search for a ride type 1")
                    println("If you want to buy a ticket type 2")
                    println("If you want to exit type 0")
                    choice2 = readLine()!!.toInt()
                }
            } catch (e: IllegalArgumentException) {
                println(e.message)
                println("Please try again")
                println("Enter 1 to continue or 0 to exit")
                val continueOperation = readLine()!!.toInt()
                if (continueOperation == 0) {
                    return
                }
            }
        }
    }
}

//this work as well but the chats are too long to ss and Intellij Idea doesn't allow me to print it like Clion idk why but it is easy to
// compile and run the code