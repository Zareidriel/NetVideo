

// add a rental to this customer
void Customer::addRental(const Rental& rental) {

    rentals.push_back(rental);
}

// customer rental statement
std::string Customer::statement() const {

    // customer name
    std::string result("Rental Record for ");
    result += getName();
    result += "\n";

    // rentals
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    for (std::vector<Rental>::const_iterator it = rentals.begin(); it != rentals.end(); ++it) {

        // every rental is a rental point
        ++frequentRenterPoints;

        // new releases rented for more then one day gives a bonus rental point
        if (it->getVideo().getCode() == Video::NEW_RELEASE &&
            it->getDaysRented() > 1 )
            ++frequentRenterPoints;

        // title of rental
        result += "\t";
        result += it->getVideo().getTitle();
        result += "\t";

        double videoPrice = 0;
        switch(it->getVideo().getCode()) {

            case Video::REGULAR:
            videoPrice += 2;
            if (it->getDaysRented() > 2)
                videoPrice += (it->getDaysRented() - 2) * 1.5;
            break;

            case Video::NEW_RELEASE:
            videoPrice += it->getDaysRented() * 3;
            break;

            case Video::CHILDRENS:
            videoPrice += 1.5;
            if (it->getDaysRented() > 3)
                videoPrice += (it->getDaysRented() - 3) * 1.5;
            break;
        }

        // amount of rental
        std::ostringstream out_str_stream;
        out_str_stream << videoPrice;
        result += out_str_stream.str();
        result += "\n";

        totalAmount += videoPrice;
    }

    // total amount owed
    result += "Amount owed is: ";
    std::ostringstream out_str_stream;
    out_str_stream << totalAmount;
    result += out_str_stream.str();
    result += "\n";

    return result;
}
