#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Include for clearing the buffer function

// Define a structure to hold ticket information
struct Ticket {
    char type[20];
    char color[10];
    double base_price;
    double final_price;
    int quantity;
    double commission_rate;
    double discount_rate;
    char zone[20];
};

// Function to calculate the final price with commission
double calculate_price_with_commission(double base_price, double commission_rate) {
    return base_price * (1.0 + commission_rate);
}

// Function to clear the input buffer
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Keep reading until newline or end-of-file
    }
}

int main() {
    // Variable declarations
    int color_choice;
    int pass_choice_num;
    int continue_program;
    int num_tickets;
    int last_talk_year;
    char had_fight[10];
    
    // Define base prices for the passes
    double daily_pass_price_white = 50.0;
    double seasonal_pass_price_white = 250.0;
    double daily_pass_price_black = 40.0; // The comment suggested higher price, but the value is lower. I'll keep the value as is.
    double seasonal_pass_price_black = 200.0; // The comment suggested higher price, but the value is lower. I'll keep the value as is.

    // Current year for comparison
    const int CURRENT_YEAR = 2025;

    // Use a do-while loop to allow the user to make multiple transactions
    do {
        printf("   Welcome to the Garba Ticket System!   \n");
        
        // --- Friend/Fight Status Input and Validation ---

        printf("When did we last talk? (Enter a year before 2025 or enter 2025): ");
        if (scanf("%d", &last_talk_year) != 1) {
            printf("Invalid year input. Please restart the transaction.\n");
            clear_input_buffer();
            continue_program = 0;
            continue; // Skip the rest of the loop body
        }
        
        // Input validation for the year
        while (last_talk_year > CURRENT_YEAR) {
            printf("The last talk year cannot be in the future (%d). Enter a valid year: ", CURRENT_YEAR);
            if (scanf("%d", &last_talk_year) != 1) {
                printf("Invalid year input. Please restart the transaction.\n");
                clear_input_buffer();
                continue_program = 0;
                continue;
            }
        }
        
        // Clear buffer before reading string input
        clear_input_buffer(); 

        printf("Did we have a fight recently? (yes/no): ");
        if (scanf("%s", had_fight) != 1) {
            printf("Invalid fight status input. Please restart the transaction.\n");
            clear_input_buffer();
            continue_program = 0;
            continue;
        }

        // Input validation for 'had_fight'
        // FIX: The original code used `had_fight != 'yes'` which is incorrect for string comparison. It should use `strcmp` and a loop.
        while (strcmp(had_fight, "yes") != 0 && strcmp(had_fight, "no") != 0) {
            printf("Enter a valid answer ('yes' or 'no'): ");
            clear_input_buffer();
            if (scanf("%s", had_fight) != 1) {
                 printf("Invalid input. Please restart the transaction.\n");
                 clear_input_buffer();
                 continue_program = 0;
                 continue;
            }
        }
        
        // Define a Ticket structure to store the selected ticket details
        struct Ticket current_ticket;

        // Determine commission and zone based on the last conversation year and fight status
        // Condition 1: talked less than or equal to 1 year ago and no fight
        if ((CURRENT_YEAR - last_talk_year <= 1) && (strcmp(had_fight, "no") == 0)) {
            current_ticket.commission_rate = 0.0; // 0% commission (Best rate)
            strcpy(current_ticket.zone, "Zone A (Far from speakers - VIP)");
        } 
        // Condition 2: talked more than 3 years ago and had a fight
        else if ((CURRENT_YEAR - last_talk_year > 3) && (strcmp(had_fight, "yes") == 0)) {
            current_ticket.commission_rate = 0.30; // 30% commission (Worst rate)
            strcpy(current_ticket.zone, "Zone C (Next to speakers - Budget)");
        } 
        // Condition 3: All other scenarios (The "Neutral" case)
        else {
            current_ticket.commission_rate = 0.15; // 15% commission (Standard rate)
            strcpy(current_ticket.zone, "Zone B (Neutral zone - Standard)");
        }
        
        printf("\n-------------------------------------\n");
        printf("Your commission rate is: %.0f%%\n", current_ticket.commission_rate * 100);
        printf("Your assigned zone is: %s\n", current_ticket.zone);
        printf("-------------------------------------\n");
        
        // --- Ticket Color and Type Selection ---

        printf("\nDo you want to buy a ticket in 'white' or 'black' category?\n");
        printf("Enter 1 for White, 2 for Black: ");
        if (scanf("%d", &color_choice) != 1) {
            printf("Invalid color choice input. Exiting the program.\n");
            clear_input_buffer();
            return 1;
        }

        // Use a switch-case statement to handle the color choice
        switch (color_choice) {
            case 1:
                strcpy(current_ticket.color, "white");
                printf("\nYou have selected the 'white' category (Higher Base Price).\n");
                printf("Available Passes:\n");
                printf("1. Daily Pass (Price: $%.2f)\n", daily_pass_price_white);
                printf("2. Seasonal Pass (Price: $%.2f)\n", seasonal_pass_price_white);
                printf("Enter your choice (1 or 2): ");
                
                if (scanf("%d", &pass_choice_num) != 1) {
                    printf("Invalid pass choice input. Defaulting to Daily Pass.\n");
                    pass_choice_num = 1;
                    clear_input_buffer();
                }

                // Use a nested if-else to handle the pass type
                if (pass_choice_num == 1) {
                    strcpy(current_ticket.type, "Daily Pass");
                    current_ticket.base_price = daily_pass_price_white;
                } else if (pass_choice_num == 2) {
                    strcpy(current_ticket.type, "Seasonal Pass");
                    current_ticket.base_price = seasonal_pass_price_white;
                } else {
                    printf("Invalid pass choice. Defaulting to Daily Pass.\n");
                    strcpy(current_ticket.type, "Daily Pass");
                    current_ticket.base_price = daily_pass_price_white;
                }
                break;
            case 2:
                strcpy(current_ticket.color, "black");
                printf("\nYou have selected the 'black' category (Lower Base Price).\n");
                printf("Available Passes:\n");
                printf("1. Daily Pass (Price: $%.2f)\n", daily_pass_price_black);
                printf("2. Seasonal Pass (Price: $%.2f)\n", seasonal_pass_price_black);
                printf("Enter your choice (1 or 2): ");
                
                if (scanf("%d", &pass_choice_num) != 1) {
                    printf("Invalid pass choice input. Defaulting to Daily Pass.\n");
                    pass_choice_num = 1;
                    clear_input_buffer();
                }

                // Use a nested if-else to handle the pass type
                if (pass_choice_num == 1) {
                    strcpy(current_ticket.type, "Daily Pass");
                    current_ticket.base_price = daily_pass_price_black;
                } else if (pass_choice_num == 2) {
                    strcpy(current_ticket.type, "Seasonal Pass");
                    current_ticket.base_price = seasonal_pass_price_black;
                } else {
                    printf("Invalid pass choice. Defaulting to Daily Pass.\n");
                    strcpy(current_ticket.type, "Daily Pass");
                    current_ticket.base_price = daily_pass_price_black;
                }
                break;
            default:
                printf("Invalid color choice. Exiting the program.\n");
                return 1; // Exit on invalid input
        }

        // --- Calculation and Quantity Input ---
        
        // Calculate the price after adding commission
        current_ticket.final_price = calculate_price_with_commission(current_ticket.base_price, current_ticket.commission_rate);

        printf("\nHow many tickets would you like to buy? ");
        if (scanf("%d", &num_tickets) != 1) {
            printf("Invalid number of tickets input. Defaulting to 1 ticket.\n");
            num_tickets = 1;
            clear_input_buffer();
        }

        // Validate the number of tickets using an if statement
        if (num_tickets <= 0) {
            printf("Invalid number of tickets. Defaulting to 1 ticket.\n");
            num_tickets = 1;
        }

        current_ticket.quantity = num_tickets;

        // Determine discount based on the number of tickets purchased
        if (num_tickets > 10) {
            current_ticket.discount_rate = 0.20; // 20% off
        } else if (num_tickets > 5) {
            current_ticket.discount_rate = 0.10; // 10% off
        } else {
            current_ticket.discount_rate = 0.0; // No discount
        }

        // Apply the discount to the final price (which already includes commission)
        double discounted_price_per_ticket = current_ticket.final_price * (1.0 - current_ticket.discount_rate);
        double total_cost = discounted_price_per_ticket * num_tickets;

        // --- Receipt Output ---

        printf("\n--- RECEIPT ---\n");
        printf("Pass Type: %s (%s category)\n", current_ticket.type, current_ticket.color);
        printf("Tickets Bought: %d\n", current_ticket.quantity);
        printf("Assigned Zone: %s\n", current_ticket.zone);
        printf("----------------\n");
        printf("Base Price per ticket: $%.2f\n", current_ticket.base_price);
        printf("Commission (%.0f%%): $%.2f\n", current_ticket.commission_rate * 100, current_ticket.base_price * current_ticket.commission_rate);
        printf("Price after commission: $%.2f\n", current_ticket.final_price);
        printf("Discount (%.0f%%): $%.2f\n", current_ticket.discount_rate * 100, current_ticket.final_price * current_ticket.discount_rate);
        printf("Final Price per ticket: $%.2f\n", discounted_price_per_ticket);
        printf("----------------\n");
        printf("Total Cost: $%.2f\n", total_cost);
        printf("----------------\n");

        // --- Continue Loop Prompt ---

        printf("Do you want to make another purchase? (1 for Yes, 0 for No): ");
        
        // FIX: Replaced original input clearing logic with a custom, more reliable function and simplified the check.
        if (scanf("%d", &continue_program) != 1) {
            printf("Invalid input. Exiting.\n");
            clear_input_buffer(); // Clear any non-integer input
            continue_program = 0;
        }

    } while (continue_program == 1); // Loop continues if user enters 1

    printf("\nThank you for using the Garba Ticket System. Goodbye! 👋\n");

    return 0;
}