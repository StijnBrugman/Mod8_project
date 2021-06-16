import datetime
from dateutil.relativedelta import relativedelta
import copy

class Converter():

    def __init__(self):
        self.old_raw_date = {'encoder_year': 0,'encoder_month': 0,'encoder_day': 0}
        self.date_boundary_ls = [datetime.datetime(1950, 1, 1), datetime.datetime(2020, 12, 31)]
        self.date = datetime.datetime(2020, 3, 31)

    def update_date(self, data_dict):
        if self.old_raw_date == data_dict:
            return
        difference_date_dic = {k: data_dict[k] - self.old_raw_date[k] for k in self.old_raw_date}
        self.old_raw_date = data_dict
        self.date = self.convert(difference_date_dic)

    def convert(self, data_dict):
        self.date += relativedelta(years=data_dict['encoder_year'], months=data_dict['encoder_month'], days=data_dict['encoder_day'])

        # Check if the date is within the boundaries, if not turn it to the other side
        if self.date_boundary() != 2:
            self.date = self.date_boundary_ls[self.date_boundary()]

        return self.date

    def date_boundary(self):
        """
        code:
        {
            '0': Upper boundary is violated
            '1': Lower boundary is violated
            '2': No boundary is violated
        }
        :return: code
        """

        if self.date_boundary_ls[1] < self.date:
            return 0
        if self.date < self.date_boundary_ls[0]:
            return 1
        return 2


    def get_date(self):
        return copy.deepcopy(self.date.strftime("%Y-%m-%d"))


