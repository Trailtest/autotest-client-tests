/*
 * (C) Copyright IBM Corp. 2004, 2005
 * Copyright (c) 2005, Intel Corporation
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
 *      Carl McAdams <carlmc@us.ibm.com>
 *      Xiaowei Yang <xiaowei.yang@intel.com>
 *
 * Spec:        HPI-B.01.01
 * Function:    saHpiSensorEventEnableSet
 * Description:   
 *   Call saHpiSensorEventEnableSet on a sensor which does not
 *   support the changing of the event enable status.
 *   Expected return: SA_ERR_HPI_READ_ONLY.
 * Line:        P88-20:P88-21
 */
#include <stdio.h>
#include "saf_test.h"

int Test_Rdr(SaHpiSessionIdT session,
	     SaHpiResourceIdT resourceId, SaHpiRdrT rdr)
{
	SaErrorT status;
	int retval = SAF_TEST_UNKNOWN;
	SaHpiSensorNumT s_num = 0;
	SaHpiBoolT Enable = SAHPI_FALSE;

	if (rdr.RdrType == SAHPI_SENSOR_RDR) {
		s_num = rdr.RdrTypeUnion.SensorRec.Num;

		if (rdr.RdrTypeUnion.SensorRec.EventCtrl != SAHPI_SEC_READ_ONLY)
			retval = SAF_TEST_NOTSUPPORT;	// Event enabled can be changed
	} else			// Non-Sensor RDR
		retval = SAF_TEST_NOTSUPPORT;

	if (retval == SAF_TEST_UNKNOWN) {
		//
		//  Call saHpiSensorEventEnableSet on a sensor which does not
		//   support the changing of the event enable status.
		//
		status = saHpiSensorEventEnableSet(session,
						   resourceId, s_num, Enable);
		if (status != SA_ERR_HPI_READ_ONLY) {
			e_print(saHpiSensorEventEnableSet,
				SA_ERR_HPI_READ_ONLY, status);
			retval = SAF_TEST_FAIL;
		} else
			retval = SAF_TEST_PASS;
	}
	return (retval);
}

int Test_Resource(SaHpiSessionIdT session,
		  SaHpiRptEntryT report, callback2_t func)
{
	int retval = SAF_TEST_UNKNOWN;

	if (report.ResourceCapabilities & SAHPI_CAPABILITY_SENSOR)
		retval = do_resource(session, report, func);
	else			//Resource Does not support Sensors
		retval = SAF_TEST_NOTSUPPORT;

	return (retval);
}

/**********************************************************
*   Main Function
*      takes no arguments
*      
*       returns: SAF_TEST_PASS when successfull
*                SAF_TEST_FAIL when an unexpected error occurs
*************************************************************/
int main(int argc, char **argv)
{
	int retval = SAF_TEST_UNKNOWN;

	retval = process_all_domains(Test_Resource, Test_Rdr, NULL);

	return (retval);
}
