// File:   kirchoffs.c
// Author: Gregory K. Bowne
// Date:   10 APR 2001
// Time:   1:35:45
// Brief:  This program does Kirchoff's calculations in C.

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	double resistance;
	double current;
	double voltage;
	double conductance;
	double temperatureCoefficient;
	double powerRating;
	int *connectedNodes;   // Array of node indices this resistor is connected to
	int numConnectedNodes; // Number of nodes connected
} Resistor;

typedef struct
{
	double current;
	double voltage;
	double charge;		// Additional property for advanced calculations
	double capacitance; // Additional property for capacitance
	double inductance;	// Additional property for inductance
	double impedance;	// Additional property for impedance
} Node;

typedef struct
{
	Resistor *resistors;
	int numResistors;
	Node *nodes;
	int numNodes;
} Circuit;

Circuit *initializeCircuit(int numResistors, int numNodes)
{
	Circuit *circuit = malloc(sizeof(Circuit));
	circuit->resistors = malloc(numResistors * sizeof(Resistor));
	circuit->nodes = malloc(numNodes * sizeof(Node));
	circuit->numResistors = numResistors;
	circuit->numNodes = numNodes;
	return circuit;
}

void initializeResistor(Resistor *resistor, double resistance, double conductance, int numConnectedNodes, int *connectedNodes)
{
	resistor->resistance = resistance;
	resistor->conductance = conductance;
	resistor->connectedNodes = malloc(numConnectedNodes * sizeof(int));
	resistor->numConnectedNodes = numConnectedNodes;
	memcpy(resistor->connectedNodes, connectedNodes, numConnectedNodes * sizeof(int));
}

void initializeNode(Node *node, double current, double voltage)
{
	node->current = current;
	node->voltage = voltage;
}

void addResistorNodeConnection(Resistor *resistor, int nodeIndex)
{
	// Allocate more memory for the new connection
	int *newConnectedNodes = realloc(resistor->connectedNodes, (resistor->numConnectedNodes + 1) * sizeof(int));
	if (!newConnectedNodes)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		return;
	}
	resistor->connectedNodes = newConnectedNodes;
	resistor->connectedNodes[resistor->numConnectedNodes++] = nodeIndex;
}

// Function to dynamically update node properties
void updateNodeProperties(Node *node, double newCapacitance, double newInductance)
{
	node->capacitance = newCapacitance;
	node->inductance = newInductance;
}

void addNodeToCircuit(Circuit *circuit)
{
    // Allocate memory for the new node
    Node *newNodes = realloc(circuit->nodes, (circuit->numNodes +  1) * sizeof(Node));
    if (!newNodes) {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
    }
    circuit->nodes = newNodes;

    // Initialize the new node (you can add more initializations as needed)
    initializeNode(&circuit->nodes[circuit->numNodes],  0.0,  0.0); // Assuming  0.0 for current and voltage as placeholders

    // Increment the number of nodes
    circuit->numNodes++;
}


// Function to check if a resistor is connected to a specific node
bool isResistorConnectedToNode(Resistor resistor, int nodeIndex)
{
	for (int i = 0; i < resistor.numConnectedNodes; i++)
	{
		if (resistor.connectedNodes[i] == nodeIndex)
		{
			return true;
		}
	}
	return false;
}

void updateResistorValues(Resistor *resistor, double newResistance, double newConductance)
{
	resistor->resistance = newResistance;
	resistor->conductance = newConductance;
	// Add more updates as needed
}

void applyKirchhoffsLaws(Circuit *circuit)
{
	// Apply KVL
	for (int i = 0; i < circuit->numNodes; i++)
	{
		double voltageSum = 0;
		double currentSum = 0;

		for (int j = 0; j < circuit->numResistors; j++)
		{
			if (isResistorConnectedToNode(circuit->resistors[j], i))
			{
				// Assuming you have a way to calculate the voltage and current across the resistor
				voltageSum += circuit->resistors[j].voltage;
				currentSum += circuit->resistors[j].current;
			}
		}

		circuit->nodes[i].voltage = voltageSum;
		circuit->nodes[i].current = currentSum;
	}

	// Apply KCL - Calculate total current entering and leaving each node
	for (int i = 0; i < circuit->numNodes; i++)
	{
		double totalCurrent = 0;

		for (int j = 0; j < circuit->numResistors; j++)
		{
			if (isResistorConnectedToNode(circuit->resistors[j], i))
			{
				totalCurrent += circuit->resistors[j].current;
			}
		}

		// Assuming nodes[i].current is the sum of the currents
		circuit->nodes[i].current = totalCurrent;
	}
}

void printCircuitResults(Circuit *circuit)
{
	printf("Node Voltages:\n");
	for (int i = 0; i < circuit->numNodes; i++)
	{
		printf("Node %d: %.2fV\n", i, circuit->nodes[i].voltage);
	}

	printf("\nNode Currents:\n");
	for (int i = 0; i < circuit->numNodes; i++)
	{
		printf("Node %d: %.2fV, %.2fA, %.2fC\n", i, circuit->nodes[i].voltage, circuit->nodes[i].current, circuit->nodes[i].charge);
	}
}

void freeCircuit(Circuit *circuit)
{
	for (int i = 0; i < circuit->numResistors; i++)
	{
		free(circuit->resistors[i].connectedNodes);
	}
	free(circuit->resistors);
	free(circuit->nodes);
	free(circuit);
}

int main()
{
	Circuit *circuit = initializeCircuit(3, 4);
	if (!circuit)
	{
		fprintf(stderr, "Memory allocation failed.\n");
		return 1;
	}
	// Initialize circuit elements and nodes here

	// Dynamically add or remove resistors/nodes as needed during runtime
	addResistorNodeConnection(&circuit->resistors[0], 2);
	updateNodeProperties(&circuit->nodes[1], 10.5, 3.2);

	applyKirchhoffsLaws(circuit);
	printCircuitResults(circuit);

	free(circuit->resistors);
	free(circuit->nodes);
	free(circuit);
	return 0;
}