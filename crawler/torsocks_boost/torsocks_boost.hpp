#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/intrusive/slist.hpp>
#include <string>
#include <iostream>

/*
 * Onion entry in the pool. This is to map a cookie IP to an .onion address in
 * the connect() process.
 */
struct OnionEntry : public boost::intrusive::slist_base_hook<> {
	/*
	 * It's always an IPv4 which is taken from the onion IP range.
	 */
	boost::asio::ip::address ip;

	/*
	 * Maximum host name length plus one for the NULL terminated byte.
	 */
	std::string hostname;

public:
    OnionEntry();
    ~OnionEntry();

};



class OnionPool
{
private:
    boost::asio::ip::address ip_subnet;
    boost::mutex lock;
    uint32_t count;
public:
    OnionPool();
    ~OnionPool();
    /*
	 * Array of onion entry indexed by cookie position. For instance, using the
	 * IP range 127.0.69.0/24, the array is of maximum size 255 and address
	 * 127.0.69.32 points to the 32th position in the array.
	 */
    boost::intrusive::slist<OnionEntry> entries;

};



