#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

struct Pass {
	char firstName[40];
	char lastName[40];
	char call[13];
	char car[7];
	enum status stat;
	int id;
	int used;
	int number;
	struct Pass* next;
};

enum status {
	active,
	disabled,
	vacation,
	lost,
	broken
};

int mal = 0, fr = 0;

struct Pass* insert(int* n, struct Pass* q, char first_Name[], char last_Name[], char Call[], char Car[], enum status s, int ID, int Used) {

	struct Pass* new1 = malloc(sizeof(struct Pass)); mal++;
	strcpy(new1->firstName, first_Name);
	strcpy(new1->lastName, last_Name);
	strcpy(new1->call, Call);
	strcpy(new1->car, Car);
	new1->stat = s;
	new1->id = ID;
	new1->used = Used;
	if (q == NULL) {
		q = new1;
		q->next = NULL;
		q->number = 0;
	}
	else {
		struct Pass* t = q;
		while (t->next != NULL) t = t->next;
		t->next = new1;
		new1->next = NULL;
		new1->number = *n;
	}
	*n = *n + 1;
	return(q);
}

int select(struct Pass* q, char c, int* num, int* selected) {
	int FieldsOrd[7];
	*num = 0;
	char Signs[7][5];
	char A[7][200];
	int B[7];
	char all[14][200];
	int i, narg, j, r, y, k = -1;

	for (j = 0; j <= 6; j++) {
		FieldsOrd[j] = 0; strcpy(Signs[j], "\0"); strcpy(A[j], "\0"); B[j] = 0;
	}

	narg = 0;
	while (c != '\n') {
		while (c == ' ') scanf("%c", &c);
		j = 0;
		while (c != ' ' && c != '\n') {
			all[narg][j] = c;
			j++;
			scanf("%c", &c);
		}
		all[narg][j] = '\0';
		narg++;
	}

	int fnum;
	char field[20];
	for (j = 0; j < narg; j++) {
		i = 0;
		while ((all[j][i] != '=') && (all[j][i] != '!') && (all[j][i] != '>') && (all[j][i] != '<') && (all[j][i] != '/')) {
			if (all[j][i] == '\0') {
				printf("Incorrect 121 %s\n", all[j]);
				return 1;
			}
			field[i] = all[j][i];
			i++;
		}
		field[i] = '\0';
		if (strcmp(field, "first_name") == 0) fnum = 0;
		else if (strcmp(field, "last_name") == 0) fnum = 1;
		else if (strcmp(field, "call") == 0) fnum = 2;
		else if (strcmp(field, "car") == 0) fnum = 3;
		else if (strcmp(field, "status") == 0) fnum = 4;
		else if (strcmp(field, "id") == 0) fnum = 5;
		else if (strcmp(field, "used") == 0) fnum = 6;
		else {
			printf("incorrect 136, %s\n", field);
			return 1;
		}
		FieldsOrd[fnum] = j + 1;
		if (all[j][i] == '=') {
			Signs[fnum][0] = '=';
			Signs[fnum][1] = '\0';
			i++;
		}
		else if (all[j][i] == '!' && all[j][i + 1] == '=') {
			Signs[fnum][0] = '!';
			Signs[fnum][1] = '=';
			Signs[fnum][2] = '\0';
			i += 2;
		}
		else if (all[j][i] == '>' && all[j][i + 1] == '=') {
			Signs[fnum][0] = '>';
			Signs[fnum][1] = '=';
			Signs[fnum][2] = '\0';
			i += 2;
		}
		else if (all[j][i] == '<' && all[j][i + 1] == '=') {
			Signs[fnum][0] = '<';
			Signs[fnum][1] = '=';
			Signs[fnum][2] = '\0';
			i += 2;
		}
		else if (all[j][i] == '>') {
			Signs[fnum][0] = '>';
			Signs[fnum][1] = '\0';
			i++;
		}
		else if (all[j][i] == '<') {
			Signs[fnum][0] = '<';
			Signs[fnum][1] = '\0';
			i++;
		}
		else if (all[j][i] == '/' && all[j][i + 1] == 'i' && all[j][i + 2] == 'n' && all[j][i + 3] == '/') {
			Signs[fnum][0] = '/';
			Signs[fnum][1] = 'i';
			Signs[fnum][2] = 'n';
			Signs[fnum][3] = '/';
			Signs[fnum][4] = '\0';
			i += 4;
		}
		else {
			printf("incorrect 182\n");
			return 1;
		}

		int j1;
		if (fnum < 5 || strcmp(Signs[fnum], "/in/") == 0) {
			j1 = 0;
			while (all[j][i] != '\0') {
				A[fnum][j1] = all[j][i];
				i++;
				j1++;
			}
			A[fnum][j1] = '\0';
			if (fnum == 4 && strcmp(Signs[fnum], "/in/") != 0) {
				if (strcmp(A[4], "active") == 0) B[4] = active;
				else if (strcmp(A[4], "disabled") == 0) B[4] = disabled;
				else if (strcmp(A[4], "vacation") == 0) B[4] = vacation;
				else if (strcmp(A[4], "lost") == 0) B[4] = lost;
				else if (strcmp(A[4], "broken") == 0) B[4] = broken;
				else return(1);
			}
		}
		else {
			B[fnum] = 0;
			while (all[j][i] != '\0') {
				B[fnum] = B[fnum] * 10 + (all[j][i] - '0');
				i++;
			}
		}
	}

	r = 0;
	
	struct Pass* t = q;
	int l = 0, i1, i2, i3, x;
	char v[40];
	while (1) {
		y = 0;
		k++;
		for (i = 1; i <= narg; i++) {
			j = 0;
			while (FieldsOrd[j] != i) j++;
			if (j == 0) {

				if (strcmp(Signs[j], "=") == 0) {
					if (strcmp(t->firstName, A[j]) == 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (strcmp(t->firstName, A[j]) > 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (strcmp(t->firstName, A[j]) < 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (strcmp(t->firstName, A[j]) >= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (strcmp(t->firstName, A[j]) <= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (strcmp(t->firstName, A[j]) != 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 471\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						if (strcmp(t->firstName, v) == 0) y++;
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 486\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 492\n");
					return(1);
				}

			}
			else if (j == 1) {

				if (strcmp(Signs[j], "=") == 0) {
					if (strcmp(t->lastName, A[j]) == 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (strcmp(t->lastName, A[j]) > 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (strcmp(t->lastName, A[j]) < 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (strcmp(t->lastName, A[j]) >= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (strcmp(t->lastName, A[j]) <= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (strcmp(t->lastName, A[j]) != 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 526\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						if (strcmp(t->lastName, v) == 0) y++;
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 541\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 547\n");
					return(1);
				}

			}
			else if (j == 2) {

				if (strcmp(Signs[j], "=") == 0) {
					if (strcmp(t->call, A[j]) == 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (strcmp(t->call, A[j]) > 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (strcmp(t->call, A[j]) < 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (strcmp(t->call, A[j]) >= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (strcmp(t->call, A[j]) <= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (strcmp(t->call, A[j]) != 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 581\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						if (strcmp(t->call, v) == 0) y++;
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 596\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 602\n");
					return(1);
				}

			}
			else if (j == 3) {

				if (strcmp(Signs[j], "=") == 0) {
					if (strcmp(t->car, A[j]) == 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (strcmp(t->car, A[j]) > 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (strcmp(t->car, A[j]) < 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (strcmp(t->car, A[j]) >= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (strcmp(t->car, A[j]) <= 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (strcmp(t->car, A[j]) != 0) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 636\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						if (strcmp(t->car, v) == 0) y++;
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 651\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 657\n");
					return(1);
				}

			}
			else if (j == 4) {

				if (strcmp(Signs[j], "=") == 0) {
					if (t->stat == B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (t->stat > B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (t->stat < B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (t->stat >= B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (t->stat <= B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (t->stat != B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 691\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						if (strcmp("active", v) == 0) { if (t->stat == active) y++; }
						else if (strcmp("disabled", v) == 0) { if (t->stat == disabled) y++; }
						else if (strcmp("vacation", v) == 0) { if (t->stat == vacation) y++; }
						else if (strcmp("lost", v) == 0) { if (t->stat == lost) y++; }
						else if (strcmp("broken", v) == 0) { if (t->stat == broken) y++; }
						else {
							printf("Incorrect 710\n");
							return(1);
						}
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 714\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 720\n");
					return(1);
				}

			}
			else if (j == 5) {

				if (strcmp(Signs[j], "=") == 0) {
					if (t->id == B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (t->id > B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (t->id < B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (t->id >= B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (t->id <= B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (t->id != B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 754\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						x = 0;
						for (i3 = 0; i3 < i2; i3++) {
							x = x * 10 + v[i3] - '0';
						}
						if (x == t->id) y++;
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 773\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 779\n");
					return(1);
				}

			}
			else if (j == 6) {

				if (strcmp(Signs[j], "=") == 0) {
					if (t->used == B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">") == 0) {
					if (t->used > B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<") == 0) {
					if (t->used < B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], ">=") == 0) {
					if (t->used >= B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "<=") == 0) {
					if (t->used <= B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "!=") == 0) {
					if (t->used != B[j]) y++;
					else break;
				}
				else if (strcmp(Signs[j], "/in/") == 0) {
					c = A[j][1];
					if (A[j][0] != '[') {
						printf("Incorrect 813\n");
						return(1);
					}
					i1 = 2;
					while (1) {
						i2 = 0;
						while (c != ',' && c != ']' && c != '\n') {
							v[i2] = c;
							c = A[j][i1];
							i1++;
							i2++;
						}
						v[i2] = '\0';
						x = 0;
						for (i3 = 0; i3 < i2; i3++) {
							x = x * 10 + v[i3] - '0';
						}
						if (x == t->used) y++;
						if (c == ']') break;
						if (c == '\n') { printf("Incorrect 832\n"); return(1); }
						c = A[j][i1];
						i1++;
					}
				}
				else {
					printf("Incorrect 838\n");
					return(1);
				}

			}
		}

		if (y == narg) {
			*num = *num + 1;
			*(selected + l) = k;
			l++;
		}
		if (t->next == NULL) break;
		t = t->next;
	}
	return(r);
}

void Print(struct Pass* q) {

	while (q != NULL) {
		printf("_______No %d________\n", q->number);
		printf("first name: %s\n", q->firstName);
		printf("last name: %s\n", q->lastName);
		printf("Phone number: %s\n", q->call);
		printf("Car number: %s\n", q->car);
		switch (q->stat) {
		case active:
			printf("Status: active\n");
			break;
		case disabled:
			printf("Status: disabled\n");
			break;
		case vacation:
			printf("Status: vacation\n");
			break;
		case lost:
			printf("Status: lost\n");
			break;
		case broken:
			printf("Status: broken\n");
			break;
		}
		printf("ID: %d\n", q->id);
		printf("Number of usings: %d\n", q->used);
		q = q->next;

	}
}

void main() {
	int N = 0;

	struct Pass* p = NULL;
	char operation[30] = { 0 };
	char fN[50] = { 0 }, lN[50] = { 0 }, Call[13] = { 0 }, Car[7] = { 0 };
	int Id, USED;
	enum status st;
	int i, nf, j, r = 0, n = 0, k, l, i1, j1;
	int* sel;
	char c;
	char field[50] = { 0 }, value[50] = { 0 };
	int FieldsOrd[7];
	char Update[7][50];
	char Fields[7][50];
	char Incorrect[21] = { 0 };
	char fieldn[30];

	for (i = 0; i < 7; i++) Fields[i][0] = '\0';

	while (1) {
		printf("Command:\n");
		i = 0;
		scanf("%c", &c);
		while (c != ' ' && c != '\n') {
			operation[i] = c;
			i++;
			scanf("%c", &c);
		}
		operation[i] = '\0';

		if (strcmp(operation, "break") == 0) break;

		if (strcmp(operation, "print") == 0) Print(p);

		if (strcmp(operation, "select") == 0) {
			sel = (int*)malloc(N * sizeof(int)); mal++;
			for (j = 0; j < N; j++) sel[j] = -1;

			for (j = 0; j < 8; j++) FieldsOrd[j] = 0;
			while (c == ' ') scanf("%c", &c);
			j = 1;
			r = 0;
			while (c != ' ') {
				int t = 0;
				while (c != ',' && c != ' ' && c != '\n') {
					fieldn[t] = c;
					t++;
					scanf("%c", &c);
				}
				fieldn[t] = '\0';
				if (strcmp(fieldn, "first_name") == 0) FieldsOrd[0] = j;
				else if (strcmp(fieldn, "last_name") == 0) FieldsOrd[1] = j;
				else if (strcmp(fieldn, "call") == 0) FieldsOrd[2] = j;
				else if (strcmp(fieldn, "car") == 0) FieldsOrd[3] = j;
				else if (strcmp(fieldn, "status") == 0) FieldsOrd[4] = j;
				else if (strcmp(fieldn, "id") == 0) FieldsOrd[5] = j;
				else if (strcmp(fieldn, "used") == 0) FieldsOrd[6] = j;
				else {
					printf("incorrect %s\n", fieldn);
					r = 1;
					break;
				}
				if (c == ' ' || c == '\n') break;
				scanf("%c", &c);
				j++;
				//printf("%s\n", fieldn);
			}
			//printf("%s\n", fieldn);
			if (r) continue;

			r = select(p, c, &n, sel);
			struct Pass* g = p;
			l = 0;
			nf = 0;

			for (j = 0; j < 7; j++) {
				if (FieldsOrd[j] != 0) nf++;
			}

			printf("\nSelect:%d\n", n);

			for (j = 0; j < N; j++) {
			
				if (sel[l] == j) {
					l++;
					for (i1 = 1; i1 <= nf; i1++) {
						j1 = 0;
						while (FieldsOrd[j1] != i1) j1++;
						if (j1 == 0) printf("first_name=%s ", g->firstName);
						else if (j1 == 1) printf("last_name=%s ", g->lastName);
						else if (j1 == 2) printf("call=%s ", g->call);
						else if (j1 == 3) printf("car=%s ", g->car);
						else if (j1 == 4) {
							if (g->stat = active) printf("status=active ");
							else if (g->stat = disabled) printf("status=disabled ");
							else if (g->stat = vacation) printf("status=vacation ");
							else if (g->stat = lost) printf("status=lost ");
							else if (g->stat = broken) printf("status=broken ");
						}
						else if (j1 == 5) printf("id=%d ", g->id);
						else if (j1 == 6) printf("used=%d ", g->used);
					}
					printf("\n");
				}
				g = g->next;
			}
			free(sel); fr++;
		}

		if (strcmp(operation, "insert") == 0) {
			k = 0;
			r = 0;
			while (c != '\n') {
				while (c == ' ') {
					scanf("%c", &c);
				}
				j = 0;
				while (c != '=') {
					field[j] = c;
					scanf("%c", &c);
					j++;
				}
				field[j] = '\0';
				j = 0;
				scanf("%c", &c);
				while (c != ',' && c != '\n') {
					value[j] = c;
					scanf("%c", &c);
					j++;
				}
				value[j] = '\0';
				if (c != '\n') scanf("%c", &c);
				if (strcmp(field, "first_name") == 0) strcpy(fN, value);
				else if (strcmp(field, "last_name") == 0) strcpy(lN, value);
				else if (strcmp(field, "call") == 0) strcpy(Call, value);
				else if (strcmp(field, "car") == 0) strcpy(Car, value);
				else if (strcmp(field, "status") == 0) {
					if (strcmp(value, "active") == 0) st = active;
					else if (strcmp(value, "disabled") == 0) st = disabled;
					else if (strcmp(value, "vacation") == 0) st = vacation;
					else if (strcmp(value, "lost") == 0) st = lost;
					else if (strcmp(value, "broken") == 0) st = broken;
					else {
						printf("incorrect\n");
						break;
					}
				}
				else if (strcmp(field, "id") == 0) {
					Id = 0;
					for (int l = 0; l < j; l++) {
						Id = Id * 10 + (value[l] - '0');
					}
				}
				else if (strcmp(field, "used") == 0) {
					USED = 0;
					for (int l = 0; l < j; l++) {
						USED = USED * 10 + (value[l] - '0');
					}
				}
				else {
					printf("Incorrect field name\n");
					r = 1;
					break;
				}
				k++;
			}
			if (r || k != 7) {
				printf("incorrect command\n");
				continue;
			}
			p = insert(&N, p, fN, lN, Call, Car, st, Id, USED);
		}

		if (strcmp(operation, "delete") == 0) {
			sel = (int*)malloc(N * sizeof(int)); mal++;
			for (j = 0; j < N; j++) sel[j] = -1;
			r = select(p, c, &n, sel);
			printf("Delete:%d\n", n);
			struct Pass* g = p;
			struct Pass* m = g->next;
			int first = 0;
			for (j = 0; j < n; j++) {
				g = p;
				if (sel[j] == first) {
					p = p->next;
					free(g); fr++;
					if (p != NULL) first = p->number;
				}
				else {
					while (g->next->number != sel[j]) g = g->next;
					m = g->next;
					g->next = m->next;
					free(m); fr++;
				}
				N--;
			}
			g = p;
			for (j = 0; j < N - 1; j++) {
				g->number = j;
				g = g->next;
			}
			g->number = N - 1;
			free(sel); fr++;
		}

		if (strcmp(operation, "update") == 0) {
			for (j = 0; j < 7; j++) Update[j][0] = '\0';
			sel = (int*)malloc(N * sizeof(int)); mal++;
			for (j = 0; j < N; j++) sel[j] = -1;

			r = 0;
			for (j = 0; j < 8; j++) FieldsOrd[j] = 0;
			while (c == ' ') scanf("%c", &c);
			j = 0;
			while (c != ' ') {
				int j1 = 0;
				while (c != '=') {
					fieldn[j1] = c;
					scanf("%c", &c);
					j1++;
				}
				fieldn[j1] = '\0';
				scanf("%c", &c);
				if (strcmp(fieldn, "first_name") == 0) FieldsOrd[0] = j + 1;
				else if (strcmp(fieldn, "last_name") == 0) FieldsOrd[1] = j + 1;
				else if (strcmp(fieldn, "call") == 0) FieldsOrd[2] = j + 1;
				else if (strcmp(fieldn, "car") == 0) FieldsOrd[3] = j + 1;
				else if (strcmp(fieldn, "status") == 0) FieldsOrd[4] = j + 1;
				else if (strcmp(fieldn, "id") == 0) FieldsOrd[5] = j + 1;
				else if (strcmp(fieldn, "used") == 0) FieldsOrd[6] = j + 1;
				else {
					printf("incorrect\n");
					r = 1;
					break;
				}
				j1 = 0;
				while (c != ',' && c != ' ') {
					Update[j][j1] = c;
					j1++;
					scanf("%c", &c);
				}
				Update[j][j1] = '\0';
				if (c == ' ') break;
				scanf("%c", &c);
				j++;
			}
			if (r) continue;

			r = select(p, c, &n, sel);
			printf("Update:%d\n", n);
			struct Pass* g = p;
			l = 0;
			nf = 0;
			for (j = 0; j < 7; j++) {
				if (FieldsOrd[j] != 0) nf++;
			}
			for (j = 0; j < N; j++) {
				if (sel[l] == j) {
					l++;
					if (FieldsOrd[0] != 0) {
						strcpy(g->firstName, Update[FieldsOrd[0] - 1]);
					}
					if (FieldsOrd[1] != 0) {
						strcpy(g->lastName, Update[FieldsOrd[1] - 1]);
					}
					if (FieldsOrd[2] != 0) {
						strcpy(g->call, Update[FieldsOrd[2] - 1]);
					}
					if (FieldsOrd[3] != 0) {
						strcpy(g->car, Update[FieldsOrd[3] - 1]);
					}
					if (FieldsOrd[4] != 0) {
						if (strcmp(Update[FieldsOrd[4] - 1], "active") == 0) g->stat = active;
						else if (strcmp(Update[FieldsOrd[4] - 1], "disabled") == 0) g->stat = disabled;
						else if (strcmp(Update[FieldsOrd[4] - 1], "vacation") == 0) g->stat = vacation;
						else if (strcmp(Update[FieldsOrd[4] - 1], "lost") == 0) g->stat = lost;
						else if (strcmp(Update[FieldsOrd[4] - 1], "broken") == 0) g->stat = broken;
					}
					if (FieldsOrd[5] != 0) {
						int a = 0, j1 = 0;
						while (Update[FieldsOrd[5] - 1][j1] != '\0') {
							a = a * 10 + Update[FieldsOrd[5] - 1][j1] - '0';
							j1++;
						}
						g->id = a;
					}
					if (FieldsOrd[6] != 0) {
						int a = 0, j1 = 0;
						while (Update[FieldsOrd[6] - 1][j1] != '\0') {
							a = a * 10 + Update[FieldsOrd[6] - 1][j1] - '0';
							j1++;
						}
						g->used = a;
					}
				}
				g = g->next;
			}
			free(sel); fr++;
		}

		if (strcmp(operation, "uniq") == 0) {
			for (i = 0; i < 7; i++) FieldsOrd[i] = 0;

			while (c == ' ') scanf("%c", &c);
			i = 0;
			while (1) {
				j = 0;
				while (c != ',' && c != '\n' && c != ' ') {
					Fields[i][j] = c;
					scanf("%c", &c);
					j++;
				}
				Fields[i][j] = '\0';
				if (strcmp(Fields[i], "first_name") == 0) FieldsOrd[0] = i + 1;
				else if (strcmp(Fields[i], "last_name") == 0) FieldsOrd[1] = i + 1;
				else if (strcmp(Fields[i], "call") == 0) FieldsOrd[2] = i + 1;
				else if (strcmp(Fields[i], "car") == 0) FieldsOrd[3] = i + 1;
				else if (strcmp(Fields[i], "status") == 0) FieldsOrd[4] = i + 1;
				else if (strcmp(Fields[i], "id") == 0) FieldsOrd[5] = i + 1;
				else if (strcmp(Fields[i], "used") == 0) FieldsOrd[6] = i + 1;
				else {
					printf("Incorrect field name: %s\n", Fields[i]);
					for (j1 = 0; j <= i; j++) {
						printf("Fields[%d]: %s\n", j1, Fields[j1]);
					}
					break;
				}
				i++;
				if (c == '\n') break;
				scanf("%c", &c);
			}

			//for (i = 0; i < 7; i++) printf("FieldsOrd[%d]: %d\n", i, FieldsOrd[i]);

			nf = i;

			int* Del;
			int* A;
			Del = (int*)malloc(N * sizeof(int)); mal++;
			A = (int*)malloc(N * sizeof(int)); mal++;
			for (i = 0; i < N; i++) Del[i] = -1;
			struct Pass* g = p;
			struct Pass* m = g->next;
			int y;
			j1 = 0;
			n = 0;

			for (i = 0; i < N - 1; i++) {
				m = g->next;
				for (j = 0; j < N; j++) A[j] = -1;
				A[0] = g->number;
				//printf("g->number: %d\n", g->number);
				i1 = 0;

				for (j = i + 1; j < N; j++) {
					y = 1;
					if (FieldsOrd[0] != 0 && strcmp(g->firstName, m->firstName) != 0) y = 0;
					else if (FieldsOrd[1] != 0 && strcmp(g->lastName, m->lastName) != 0) y = 0;
					else if (FieldsOrd[2] != 0 && strcmp(g->call, m->call) != 0) y = 0;
					else if (FieldsOrd[3] != 0 && strcmp(g->car, m->car) != 0) y = 0;
					else if (FieldsOrd[4] != 0 && g->stat != m->stat) y = 0;
					else if (FieldsOrd[5] != 0 && g->id != m->id) y = 0;
					else if (FieldsOrd[6] != 0 && g->used != m->used) y = 0;
					if (y) {
						A[i1 + 1] = m->number;
						i1++;
					}
					m = m->next;
				}


				if (A[1] != -1) {
					for (j = i1 - 1; j >= 0; j--) {
						y = 1;
						for (int h = 0; h < j1; h++) {
							if (A[j] == Del[h]) y = 0;
						}
						if (y) {
							Del[j1] = A[j];
							j1++;
						}
					}
				}

				if (g->next != NULL) g = g->next;
			}



			printf("Uniq:%d\n", j1);

			// в Del номера записей, которые удалить

			int first = 0;
			for (j = 0; j < j1; j++) {
				g = p;
				if (Del[j] == first) {
					p = p->next;
					free(g); fr++;
					if (p != NULL) first = p->number;
				}
				else {
					while (g->next->number != Del[j]) g = g->next;
					m = g->next;
					g->next = m->next;
					free(m); fr++;
				}
				N--;
			}
			g = p;
			for (j = 0; j < N - 1; j++) {
				g->number = j;
				g = g->next;
			}
			g->number = N - 1;

			free(Del); fr++;
			free(A); fr++;
		}
	}
	Print(p);
	struct Pass* t = p->next;

	for (i = 0; i < N; i++) {
		t = p->next;
		free(p); fr++;
		p = t;
	}

	printf("\nmalloc:%d", mal);
	printf("\nfree:%d", fr);
}