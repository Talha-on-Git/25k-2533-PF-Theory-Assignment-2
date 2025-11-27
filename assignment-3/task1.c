#include <stdio.h>

void extraPayment(float *loan)
{
    float extraPayment;
    printf("\nEnter the extra payment: ");
    scanf("%f", &extraPayment);
    *loan -= extraPayment;
    if (*loan < 0)
    {
        *loan = 0;
    }

}

void calculateRepayment(float loan, float interestRate, int years, int printLoanNum)
{

    char choice;
    if (loan <= 0 || years == 0)
    {
        printf("\nLoan Repayment Completed!\n");
        return;
    }

    loan += (loan * interestRate / 100);
    float installment = loan / years;
    loan -= installment;

    printf("\nYear %d: Remaining Loan = %.2f", printLoanNum, loan);
    if (loan > 0)
    {
        printf("\nDo you want to make an extra payment? (Y/N): ");
        scanf(" %c", &choice);
        if (choice == 'Y' || choice == 'y')
        {
            extraPayment(&loan);
            printf("\nRemaining Loan after extra payment = %.2f\n", loan);
        } else
        {
            printf("\ninvalid choice");
        }
    }
    
    printLoanNum++;
    calculateRepayment(loan, interestRate, years - 1, printLoanNum);
}

int main()
{
    int years;
    float interestRate, loanAmount;
    printf("\nEnter the loan amount: ");
    scanf("%f", &loanAmount);
    printf("\nEnter the interest rate: ");
    scanf("%f", &interestRate);
    printf("\nEnter the number of years: ");
    scanf("%d", &years);
    int printLoanNum = 1;
    calculateRepayment(loanAmount, interestRate, years, printLoanNum);
    return 0;
}