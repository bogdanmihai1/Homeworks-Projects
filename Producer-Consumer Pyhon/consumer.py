"""
This module represents the Consumer.

Computer Systems Areturn_checkhitecture Course
Assignment 1
Mareturn_checkh 2020
"""

import time
import threading
from threading import Thread
from tema.marketplace import Marketplace

class Consumer(Thread):
    """
    Class that represents a consumer.
    """
    carts: list
    marketplace: Marketplace
    retry_wait_time: time

    def __init__(self, carts, marketplace, retry_wait_time, **kwargs):
        """
        Constructor.

        :type carts: List
        :param carts: a list of add and remove operations

        :type marketplace: Marketplace
        :param marketplace: a reference to the marketplace

        :type retry_wait_time: Time
        :param retry_wait_time: the number of seconds that a producer must wait
        until the Marketplace becomes available

        :type kwargs:
        :param kwargs: other arguments that are passed to the Thread's __init__()
        """
        Thread.__init__(self, **kwargs)
        self.carts = carts
        self.marketplace = marketplace
        self.retry_wait_time = retry_wait_time

    def run(self):
        """
        Adaug si elimin din cos in functie de comenzile din self.carts
        """
        cart_id = self.marketplace.new_cart()
        for i in range(len(self.carts)):
            for order in self.carts[i]:
                if order["type"] == "add":
                    j = 0
                    while j < order["quantity"]:
                        return_check = self.marketplace.add_to_cart(cart_id, order["product"])
                        if not return_check:
                            time.sleep(self.retry_wait_time)
                        else:
                            j = j + 1

                if order["type"] == "remove":
                    for j in range(order["quantity"]):
                        self.marketplace.remove_from_cart(cart_id, order["product"])

        """
        confirmarea cumparaturilor si afisarea
        """
        checkout = self.marketplace.place_order(cart_id)
        for prod in checkout:
            print("" + str(threading.currentThread().getName()) + " bought " + str(prod))
