/*******************************************************************************
 *
 * This library is a C++ implementation of an algorithm designed by Robin
 * Lamarche-Perrin. This algorithm enables to aggregate sets of scalar or vector
 * data, according aggregation gain & information loss ratio parameter.
 * More information in "Robin Lamarche-Perrin, Yves Demazeau and Jean-Marc
 * Vincent. The Best-partitions Problem: How to Build Meaningful Agregations?
 * Research report RR-LIG-XXX, Laboratoire d’Informatique de Grenoble, France,
 * Feb. 2013. (forthcoming)"
 *
 * (C) Copyright (February 28th 2013) Damien Dosimont. All rights reserved.
 *
 * Damien Dosimont <damien.dosimont@imag.fr>
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3.0 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 *******************************************************************************/

#include "LPAggregWrapper.h"


LPAggregWrapper::LPAggregWrapper() :
aggregator(VectorLPAggreg()), values(vector< vector<double> >()), parts(vector<int>()){
}

LPAggregWrapper::~LPAggregWrapper() {
	for (int i=0; i<getVectorNumber(); i++)
		values[i].clear();
	values.clear();
	parts.clear();
}

void LPAggregWrapper::newVector() {
	values.push_back(vector<double>());
}

void LPAggregWrapper::addToVector(double element) {
	values[values.size()-1].push_back(element);
}

void LPAggregWrapper::addToVector(double element, int index) {
	if (index<(int)values.size())
	values[index].push_back(element);
}

int LPAggregWrapper::getVectorNumber() {
	return (int)values.size();
}

int LPAggregWrapper::getVectorSize() {
	for (int i=0; (i<getVectorNumber()-1) && (getVectorNumber()>1) ; i++){
		if (values[i].size()!=values[i+1].size())
			return -1;
	}
	if (getVectorNumber()>0)
		return values[0].size();
	else
		return -1;
}

void LPAggregWrapper::computeParts(float parameter) {
	parts.clear();
	parts=aggregator.getParts(parameter);
}

void LPAggregWrapper::computeQualities(bool normalization) {
	aggregator.setValues(values);
	aggregator.init(normalization);
}

int LPAggregWrapper::getPart(int index) {
	if (index < getPartNumber())
		return parts[index];
	return -1;
}

int LPAggregWrapper::getPartNumber() {
	return (int)parts.size();
}

void LPAggregWrapper::computeDichotomy(float threshold) {
	parameters=aggregator.getParameters(threshold);
	qualities=aggregator.getQualities();
}

int LPAggregWrapper::getParameterNumber() {
	return (int)parameters.size();
}

float LPAggregWrapper::getParameter(int index) {
	if (index < getParameterNumber())
		return parameters[index];
	return -1;
}

double LPAggregWrapper::getGainByIndex(int index) {
	if (index<(int) qualities.size())
		return qualities[index]->getGain();
	return -1;
}

double LPAggregWrapper::getGainByParameter(float parameter) {
	for (int i=0; i<(int) parameters.size(); i++)
		if (parameter==parameters[i])
		   return qualities[i]->getGain();
	return -1;
}

double LPAggregWrapper::getLossByIndex(int index) {
	if (index<(int) qualities.size())
		return qualities[index]->getLoss();
	return -1;
}

double LPAggregWrapper::getLossByParameter(float parameter) {
	for (int i=0; i<(int) parameters.size(); i++)
		if (parameter==parameters[i])
		   return qualities[i]->getLoss();
	return -1;
}
