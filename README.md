# Supermarket-management.c
Language used: C

This application enables the management of an entire supermarket. It has records of the working personnel, products in stock, best customers, etc.. 
Usually, there are more than 2 cashiers in a supermarket:with this application, each cashier has an account. That is, each cashier needs a password to access their account in order to make sales. The password is unique to each cashier, and only the boss can have access to the cashiers' accounts. 

In the morning, the boss needs to enter a password before the application opens, and then each cashier can have access to their account.

This application also tracks the best customers in order to offer discounts in the long run.
Question: How does it work?
Ans: Each customer is identified by a name, code, and type. The more a client makes purchases, the better their rank in the database. The best customers are classified as "VIP".

Also, when the quantity of a product in stock is less than or equal to the threshold quantity (fixed by the boss), he gets signaled, and he can then take appropriate actions. This avoids the supermarket to run out of stock.

Only the boss can manage the stock; that is, he is the only one able to add a new product, delete an existing product, or perform similar actions. This avoids unwanted changes that might be performed by cashiers.
