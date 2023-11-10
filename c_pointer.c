#include "c_pointer.h"
#include "pointer_functions.h"

#define DEBUG
#undef DEBUG

int main(int argc, char* argv[]) {
  CustomerState customer_state = STARTUP;
  ListManipulationState list_manipulation_state = LIST_READ;
  ReadWriteState read_write_state = READ_FIRST_NAME;
  struct CustomerList customer_list = {NULL, NULL, 0}; // Initialize empty customer list


  while(customer_state != EXIT) {
    switch(customer_state) {
      case(STARTUP):
        if (argc > 1) {
#ifdef DEBUG
          fprintf(stdout, "You entered %d arguments.\n", argc);
          fprintf(stdout, "First argument is %s\n", argv[0]);
#endif

          for (int i = 1; i < argc; i++) {
            struct CustomerNode* new_customer = (struct CustomerNode*)malloc(sizeof(struct CustomerNode));

            if (new_customer == NULL) {
              fprintf(stderr, "Failed to allocate memory for new customer\n");
              return EXIT_FAILURE;
            }

            strcpy(new_customer->first_name, argv[i]);

            fprintf(stdout, "Enter last name (Up to 20 characters): ");
            if (fgets(new_customer->last_name, sizeof(new_customer->last_name), stdin) != NULL) {
              // Remove the trailing newline character, if present
              size_t len = strlen(new_customer->last_name);
              if (len > 0 && new_customer->last_name[len - 1] == '\n') {
                new_customer->last_name[len - 1] = '\0';
              }
            } else {
              fprintf(stderr, "Error reading last name.\n");
              free(new_customer); // Free allocated memory
              return EXIT_FAILURE; // Exit with an error code
            }

            char *age_input;
            bool valid_age = false;
            do {
              printf("Enter age (0 or higher): ");
              if (fgets(age_input, sizeof(age_input), stdin) == NULL) {
                perror("Error reading input");
                EXIT_FAILURE;
              }

              if (sscanf(age_input, "%d", &new_customer->age) != 1 || new_customer->age < 0) {
              printf("Invalid input. Age must be a non-negative number. Please try again.\n");
              } else {
                valid_age = true;
              }
            } while (!valid_age);

            if (customer_list.head == NULL) {
              customer_list.head = new_customer;
              customer_list.tail = new_customer;
              customer_list.size++;
            } else {
              customer_list.tail->next = new_customer;
              customer_list.tail = new_customer;
              customer_list.size++;
            }
          }
        }

        customer_state = READY;
        break;
      case(READY):
        if (customer_list.size == 0) {
          fprintf(stdout, "Customer array currently empty. Do you want to enter a new customer? (y/n): ");
          char response[2]; // Allow space for the response and null terminator
    
          while (true) {
              printf("Customer array currently empty. Do you want to enter a new customer? (y/n): ");
              if (fgets(response, sizeof(response), stdin) == NULL) {
                  perror("Error reading input");
                  return 1;
              }
              
              // Remove newline character, if present
              response[strcspn(response, "\n")] = '\0';
              
              // Convert response to lowercase for case-insensitive comparison
              for (int i = 0; response[i]; i++) {
                  response[i] = tolower(response[i]);
              }

              if (strcmp(response, "y") == 0) {
                  printf("You chose to enter a new customer.\n");
                  // Perform actions for "yes"
                  break; // Exit the loop
              } else if (strcmp(response, "n") == 0) {
                  printf("You chose not to enter a new customer.\n");
                  // Perform actions for "no"
                  break; // Exit the loop
              } else {
                  printf("Invalid input. Please enter 'y' or 'n'.\n");
              }
          }
        }
        customer_state = CLEANUP; //Hacky to exit immediately
        break;
      case(READ):
        break;
      case(WRITE):
        break;
      case(LIST_MANIPULATION):
        switch(list_manipulation_state) {
          case(LIST_READ):
            break;
          case(LIST_WRITE):
            break;
          case(LIST_INSERT):
            break;
          case(LIST_DELETE):
            break;
        }
        break;
      case(CLEANUP):
        fprintf(stdout, "Exiting...\n");
        freeCustomerList(&customer_list);
        customer_state = EXIT;
        break;
      default:
        fprintf(stderr, "Invalid state\n");
        return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}