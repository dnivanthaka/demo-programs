/*
 * =====================================================================================
 *
 *       Filename:  q10.cpp
 *
 *    Description:  question 10
 *
 *        Version:  1.0
 *        Created:  04/15/2012 07:34:35 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  D.N. Amerasinghe (Niva), nivanthaka@gmail.com
 *        Company:  HobbyWorks
 *
 * =====================================================================================
 */

int i = 10;
const int *j = &i;

int main(int argc, char *argv[])
{
	*j = 10;

	return 0;
}
