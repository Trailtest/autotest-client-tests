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
 * Function:    saHpiSensorThresholdsGet
 * Description:   
 *   Call function on a sensor which the threshold definition
 *   is set as non-accessible (Is not threshold type).
 *   Expected return: SA_ERR_HPI_INVALID_CMD.
 * Line:        P81-20:P81-21
 */
#include <stdio.h>
#include "saf_test.h"

int Test_Rdr(SaHpiSessionIdT session,
	     SaHpiResourceIdT resourceId, SaHpiRdrT rdr)
{
	SaErrorT status;
	int retval = SAF_TEST_UNKNOWN;
	SaHpiSensorThresholdsT threshold;
	SaHpiSensorNumT s_num = 0;
	SaHpiBoolT accessible;

	if (rdr.RdrType == SAHPI_SENSOR_RDR) {
		accessible =
		    rdr.RdrTypeUnion.SensorRec.ThresholdDefn.IsAccessible;
		s_num = rdr.RdrTypeUnion.SensorRec.Num;
		if (accessible)
			retval = SAF_TEST_NOTSUPPORT;
	} else			// Non-Sensor RDR
		retval = SAF_TEST_NOTSUPPORT;

	if (retval == SAF_TEST_UNKNOWN) {
		//
		//  Call function on a sensor which the threshold definition
		//  is set as in-accessible.
		//
		status = saHpiSensorThresholdsGet(session,
						  resourceId,
						  s_num, &threshold);
		if (status != SA_ERR_HPI_INVALID_CMD) {
			if (status == SA_ERR_HPI_ENTITY_NOT_PRESENT) {
				m_print("sensor is not present.");
				retval = SAF_TEST_NOTSUPPORT;
			} else {
				e_print(saHpiSensorThresholdsGet,
					SA_ERR_HPI_INVALID_CMD
					|| SA_ERR_HPI_ENTITY_NOT_PRESENT,
					status);
				retval = SAF_TEST_FAIL;
			}
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
