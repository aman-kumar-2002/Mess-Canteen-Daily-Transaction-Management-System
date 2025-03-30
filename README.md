A CLI-based application built in C++ to manage daily transactions, menu operations, and monthly billing for a mess or canteen.
It supports both admin and student roles with functionalities for purchasing, billing, and viewing transaction history.

Features
Admin Functionality
- Add Menu Items: Add new items with ID, name, and price.  
- Remove Menu Items: Remove items by ID.  
- View Menu: Display the current menu with item details.  

Student Functionality
- View Menu: Display the menu with item IDs, names, and prices.  
- Purchase Items: Buy items by ID, and the transaction is automatically recorded.  
- View Transactions: View the complete transaction history.  
- View Monthly Bill: Enter the month (e.g., `2025-03`) to view the total bill for that period.  

Data Persistence
- Menu Data: Stored in `menu.txt`  
- Transaction Data: Stored in `transactions.txt`  
- Data is automatically saved and loaded when the program runs.


Future Enhancements
- Add user authentication with passwords for admin and students.  
- Display detailed **transaction reports** for different periods.  
- Add export to CSV functionality for better data analysis.  
- Create a GUI version using Qt for better user experience.
