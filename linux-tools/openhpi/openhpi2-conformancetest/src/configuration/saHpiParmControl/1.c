/*
 * Copyright (c) 2005, University of New Hampshire
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
 * Author(s):
 *      Lauren DeMarco <lkdm@cisunix.unh.edu>
 *
 * Function:    saHpiParmControl()
 * Description:   
 *   Call saHpiParmControl on a resource which doesn't support 
 *      parameter control.
 *   Expected return:  call returns SA_ERR_HPI_CAPABILITY
 *
 * Line:        P153-24:P153-25
 */
#include <stdio.h>
#include <unistd.h>
#include "saf_test.h"

int Test_Resource(SaHpiSessionIdT session_id, SaHpiRptEntryT rpt_entry,
		  callback2_t func)
{
	SaHpiResourceIdT resource_id = rpt_entry.ResourceId;
	SaHpiParmActionT action = SAHPI_DEFAULT_PARM;
	SaErrorT val;
	int ret = SAF_TEST_UNKNOWN;

	// Check to see if parameter control is supported       
	if (!(rpt_entry.ResourceCapabilities & SAHPI_CAPABILITY_CONFIGURATION)) {
		// Call saHpiParmControl on a resource that does not support parameter control
		val = saHpiParmControl(session_id, resource_id, action);

		if (val != SA_ERR_HPI_CAPABILITY)	// The function works abnormally 
		{
			e_print(saHpiParmControl, SA_ERR_HPI_CAPABILITY, val);
			ret = SAF_TEST_FAIL;
		} else		// The function works the way it should
			ret = SAF_TEST_PASS;
	} else {
		// Resource does not support parameter control
		ret = SAF_TEST_NOTSUPPORT;
	}

	return ret;
}

int main()
{
	int ret = SAF_TEST_UNKNOWN;

	ret = process_all_domains(Test_Resource, NULL, NULL);

	return ret;
}
