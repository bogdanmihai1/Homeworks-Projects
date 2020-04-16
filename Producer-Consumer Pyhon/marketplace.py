"""
This module represents the Marketplace.

Computer Systems Architecture Course
Assignment 1
March 2020
"""

import threading
from threading import Lock

class Marketplace:
    """
    Class that represents the Marketplace. It's the central part of the implementation.
    The producers and consumers use its methods concurrently.
    """
    queue_size_per_producer: int

    """
    initializari
    """
    producers = []
    carts = []
    bought_from = []
    products = []
    lock = Lock()
    end = False

    def __init__(self, queue_size_per_producer):
        """
        Constructor

        :type queue_size_per_producer: Int
        :param queue_size_per_producer: the maximum size of a queue associated with each producer
        """
        self.queue_size_per_producer = queue_size_per_producer

    def register_producer(self):
        """
        Returns an id for the producer that calls this.
        """
        pid = threading.currentThread().getName()
        if pid not in self.producers:
            self.producers.append(pid)
            self.products.append([])
        return pid

    def publish(self, producer_id, product):
        """
        Adds the product provided by the producer to the marketplace

        :type producer_id: String
        :param producer_id: producer id

        :type product: Product
        :param product: the Product that will be published in the Marketplace

        :returns True or False. If the caller receives False, it should wait and then try again.
        """
        pindex = self.producers.index(producer_id)
        if len(self.products[pindex]) >= self.queue_size_per_producer:
            return False
        self.products[pindex].append(product)
        return True

    def new_cart(self):
        """
        Creates a new cart for the consumer

        :returns an int representing the cart_id
        """
        self.carts.append([])
        self.bought_from.append([])
        return len(self.carts) - 1

    def add_to_cart(self, cart_id, product):
        """
        Adds a product to the given cart. The method returns

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to add to cart

        :returns True or False. If the caller receives False, it should wait and then try again
        """

        self.lock.acquire()
        found = False
        pos = 0
        self.end = True

        for i in range(len(self.products)):
            if product in self.products[i]:
                found = True
                pos = i
                break

        if not found:
            self.lock.release()
            return False

        self.carts[cart_id].append(product)
        self.bought_from[cart_id].append(pos)
        self.products[pos].remove(product)
        self.lock.release()
        return True

    def remove_from_cart(self, cart_id, product):
        """
        Removes a product from cart.

        :type cart_id: Int
        :param cart_id: id cart

        :type product: Product
        :param product: the product to remove from cart
        """
        pindex = self.carts[cart_id].index(product)

        self.carts[cart_id].remove(product)
        producer_index = self.bought_from[cart_id].pop(pindex)
        self.products[producer_index].append(product)


    def place_order(self, cart_id):
        """
        Return a list with all the products in the cart.

        :type cart_id: Int
        :param cart_id: id cart
        """
        checkout = self.carts[cart_id]
        self.carts[cart_id] = []
        self.bought_from[cart_id] = []
        return checkout

    def empty_carts(self):
        """
        Returns True if the producers should stop or False otherwise
        """
        if not self.carts:
            if self.end:
                return True
        return False
