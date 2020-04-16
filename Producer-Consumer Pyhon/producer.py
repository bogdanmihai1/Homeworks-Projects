"""
This module represents the Producer.

Computer Systems Architecture Course
Assignment 1
March 2020
"""

import time
from threading import Thread
from tema.marketplace import Marketplace

class Producer(Thread):
    """
    Class that represents a producer.
    """
    products: list
    marketplace: Marketplace
    republish_wait_time: time

    def __init__(self, products, marketplace, republish_wait_time, **kwargs):
        """
        Constructor.

        @type products: List()
        @param products: a list of products that the producer will produce

        @type marketplace: Marketplace
        @param marketplace: a reference to the marketplace

        @type republish_wait_time: Time
        @param republish_wait_time: the number of seconds that a producer must
        wait until the marketplace becomes available

        @type kwargs:
        @param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)
        self.products = products
        self.marketplace = marketplace
        self.republish_wait_time = republish_wait_time

    def run(self):
        pid = self.marketplace.register_producer()
        while not self.marketplace.empty_carts():
            for prod in self.products:
                num_prod = prod[1]
                waiting_time = prod[2]
                i = 0
                while i < num_prod:
                    return_check = self.marketplace.publish(pid, prod[0])
                    if not return_check:
                        time.sleep(waiting_time)
                    else:
                        i = i + 1
                        time.sleep(self.republish_wait_time)
