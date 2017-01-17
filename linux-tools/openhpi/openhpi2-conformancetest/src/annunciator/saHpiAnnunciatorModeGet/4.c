/*
 * (C) Copyright University of New Hampshire 2005
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307 USA.
 *
 * Authors:
 *     Donald A. Barre <dbarre@unh.edu>
 *
 * Spec:        HPI-B.01.01
 * Function:    saHpiAnnunciatorModeGet
 * Description:
 *   Attempt to get the annunciator mode for a resource 
 *   that does not support annunciators.
 *   Expected return: SA_ERR_HPI_CAPABILITY.
 * Line:        P130-26:P130-27
 */

#include <stdio.h>
#include "../include/annun_test.h"

/*************************************************************
 *
 *  Test a resource that does not support annunciators.
 *      
 *************************************************************/

int Test_Resource(SaHpiSessionIdT sessionId,
		  SaHpiRptEntryT report, callback2_t func)
{
	int retval = SAF_TEST_NOTSUPPORT;
	SaErrorT status;
	SaHpiAnnunciatorNumT a_num = 0;
	SaHpiAnnunciatorModeT mode;

	if (!hasAnnunciatorCapability(&report)) {

		status = saHpiAnnunciatorModeGet(sessionId,
						 report.ResourceId,
						 a_num, &mode);

		if (status == SA_ERR_HPI_CAPABILITY) {
			retval = SAF_TEST_PASS;
		} else {
			retval = SAF_TEST_FAIL;
			e_print(saHpiAnnunciatorModeGet, SA_ERR_HPI_CAPABILITY,
				status);
		}
	}

	return retval;
}

/*************************************************************
 *
 *  Main Program
 *      
 *************************************************************/

int main(int argc, char **argv)
{
	return process_all_domains(Test_Resource, NULL, NULL);
}
