test = {
  'name': 'ssd',
  'points': 1,
  'suites': [
    {
      'cases': [
        {
          'code': r"""
          >>> w = np.array([-3, 2, 0.5, -1]);
          >>> X = np.array([[4, -5,  2],
          ...               [5,  3, -3],
          ...               [5,  2,  1],
          ...               [8,  6,  9],
          ...               [5, -6,  2]]);
          >>> y = np.array([6, -3, 0.5, 1, 0.]);
          >>> 
          >>> ssd_cost(w, X, y)
          322.75
          """,
          'hidden': False,
          'locked': False
        }
      ],
      'scored': True,
      'setup': '',
      'teardown': '',
      'type': 'doctest'
    }
  ]
}
